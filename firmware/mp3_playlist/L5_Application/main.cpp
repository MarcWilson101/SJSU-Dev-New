/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * @brief This is the application entry point.
 * 			FreeRTOS and stdio printf is pre-configured to use uart0_min.h before main() enters.
 * 			@see L0_LowLevel/lpc_sys.h if you wish to override printf/scanf functions.
 *
 */
#include "FreeRTOS.h"
#include "task.h"
#include "tasks.hpp"
#include "LCD.hpp"
#include "queue.h"
#include "printf_lib.h"
#include "mp3SPI.hpp"
#include "mp3.hpp"
#include "ADCDriver.hpp"
#include "string"

//--function declaration--//
void gpioInit();
void suspendSendMP3_task();
void resumeSendMP3_task();
void writeReg(uint8_t address, uint8_t high, uint8_t low);

typedef enum {
	back, next
} playBack_t;

//--------globals------------//
char playlist[3][19] = { "1:track001.mp3", "1:track002.mp3", "1:track003.mp3" };
playBack_t state = next;
uint8_t trackNumber = 0;
char (*nowPlaying)[19] = &playlist[trackNumber];
char *songNamePtr = *(playlist + trackNumber);
uint8_t volume = 0x4E;
uint8_t lcdVolume = 15 - (volume / 16);
bool isPlaying = true;
float rawData;
uint8_t oldVolume;
uint8_t newVolume;
uint8_t oldLCDVolume;

//--class instantiations--//
LCD myLCD;
mp3SPI mySPI;
mp3 myMP3;
ADCDriver myADC;

//---------handles---------//
SemaphoreHandle_t pauseSemaphore = NULL;
SemaphoreHandle_t nextSemaphore = NULL;
SemaphoreHandle_t backSemaphore = NULL;
TaskHandle_t sendMP3Handle;
TaskHandle_t readSDHandle;


/**
 * 1) Gets executed when the ADC is done with a conversion.
 * 
 * 
 * 
 * 
*/
void volumeISR()
{
	//u0_dbg_printf("\n\nInside interrupt\n\n");
	myADC.clearIntFlag();
	oldVolume = volume;
	oldLCDVolume = lcdVolume;
	newVolume = 0;
	rawData = myADC.readADCRawByChannel(3);
	uint16_t intRawData = int(rawData + .5) ; //cast it into an int..
	intRawData = intRawData / 18;// divide by 18; //get 0-4000 in 0-250 range
	newVolume = 230 - intRawData; //volume is reversed on 1053
	volume = newVolume;
	if (newVolume < 0xFE && newVolume > 0x0E) // within range
	{
		lcdVolume = 15 - (volume / 16);
		writeReg(0x0B, volume, volume);
	}
	myADC.stopADC();
}


QueueHandle_t my_queue = xQueueCreate(3, sizeof(uint8_t*));
QueueHandle_t controller_queue = xQueueCreate(5, sizeof(uint8_t*));

void readSD(void *p)
{
	while(1)
    {
		state = next; //default if song ends go to next song
		bool fileOpen;

		char *SDbuffer;
		SDbuffer = (char*) malloc(sizeof(char) * 512);
		FILE *file = fopen(*nowPlaying, "r");
		
		if (file != NULL)
			fileOpen = true;

		fseek(file, 0, SEEK_END);
		int fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		songNamePtr = *(playlist + trackNumber);
		vTaskDelay(1000);
		myLCD.LCDsendCommand(CLEAR);
		vTaskDelay(100);
		myLCD.LCDsendSongName(songNamePtr, 19);
		myLCD.LCDsendVolume(lcdVolume);

		uint32_t j = 0;
		while (fileOpen) 
		{
			for (int i = 0; i < fileSize; i = i + 512) 
			{
				j++;
				if(j == 5)
				{
					j = 0;
					myADC.startADC();
					if(lcdVolume != oldLCDVolume)
					{
						myLCD.LCDsendCommand(CLEAR);
						vTaskDelay(10);
						myLCD.LCDsendSongName(songNamePtr, 19);
						vTaskDelay(10);
						myLCD.LCDsendVolume(lcdVolume);
					}
				}

				if(xSemaphoreTake(nextSemaphore, 0))
				{
					state = next;
					resumeSendMP3_task();
					break;
				}
				if(xSemaphoreTake(backSemaphore, 0))
				{
					state = back;
					resumeSendMP3_task();
					break;
				}

				fread(SDbuffer, 1, (size_t) 512, file); // Read 32byte block from SD
				xQueueSend(my_queue, &SDbuffer, portMAX_DELAY);
			} // end for loop
			fclose(file);
			fileOpen = false;
		}

		switch(state)
		{
			case next: 
				if(trackNumber != 2)
				{
					trackNumber++;
					nowPlaying++;
				}
				else
				{
					trackNumber = 0;
					nowPlaying = &playlist[0];
				}
				break;
			case back:
				if(trackNumber != 0)
				{
					trackNumber--;
					nowPlaying--;
				}
				else
				{
					trackNumber = 2;
					nowPlaying = &playlist[2];
				}

				break;
		}
		free(SDbuffer);
	}
}

void sendMP3(void *p)
{
	//u0_dbg_printf("\n--------\n--\n--\n--\n--\n----volumeUpper original: %u---\n--\n--\n--\n-------------", volumeUpper);
	
    uint8_t *mp3ptr;
	uint16_t x = 0;
	myLCD.LCDinit();
	while(1)
    {
		x = 0;
		char command;
		if (xQueueReceive(my_queue, &mp3ptr, portMAX_DELAY)) 
		{ 
			if(SW.getSwitch(1))
			{
				command = 'p';
				//u0_dbg_printf("\n\n-----pause button pressed-----\n\n");
				vTaskDelay(200);
				xQueueSend(controller_queue, &command, 0);
			}
			else if(SW.getSwitch(3))
			{
				command = 'n';
				//u0_dbg_printf("\n\n-----pause button pressed-----\n\n");
				vTaskDelay(200);
				xQueueSend(controller_queue, &command, 0);
			}
			else if(SW.getSwitch(4))
			{
				command = 'b';
				//u0_dbg_printf("\n\n-----pause button pressed-----\n\n");
				vTaskDelay(200);
				xQueueSend(controller_queue, &command, 0);
			}
			while (x < 512) 
			{
				while (myMP3.checkDREQ() == 0);
				myMP3.selectDCS();			
				for (uint8_t i = 0; i < 32; i++, mp3ptr++, x++) 
				{
					mySPI.sendByte(*mp3ptr);
				}		
				while (myMP3.checkDREQ() == 0);
				myMP3.deselectDCS();
			} // end while loop
		}
	}
}

void controller(void *p)
{
	char c;
	while(1)
	{
		//u0_dbg_printf("\n\n----inside controller-----\n\n");
		if(isPlaying)
		{
			if(xQueueReceive(controller_queue, &c, portMAX_DELAY))
			{
				//u0_dbg_printf("\n\n----c = %d-----\n\n", c);
				if(c == 'p')
				{
					//u0_dbg_printf("\n\n-----pause button pressed-----\n\n");
					vTaskDelay(100);
					suspendSendMP3_task();
					isPlaying = false;
				}
				else if(c == 'l')
				{
					//u0_dbg_printf("\n\n----play button pressed-----\n\n", c);
					vTaskDelay(100);
					resumeSendMP3_task();
				}
				else if(c == 'n')
				{
					suspendSendMP3_task();
					xSemaphoreGive(nextSemaphore);

				}
				else if(c == 'b')
				{
					suspendSendMP3_task();
					xSemaphoreGive(backSemaphore);
				}
			}
		}

		else
		{
			if(SW.getSwitch(2))
			{
				c = 'l';
				vTaskDelay(200);
				isPlaying = true;
				resumeSendMP3_task();
			}
		}
	}
}

int main(void)
{
	mySPI.mp3SPIinit();
	gpioInit();
	myMP3.mp3Init();	
	isr_register(ADC_IRQn, volumeISR);
	myADC.adcInitBurstMode(3);
    myADC.adcSelectPin(3);
	myADC.startADC();

	nextSemaphore = xSemaphoreCreateBinary();
	backSemaphore = xSemaphoreCreateBinary();

    writeReg(0x03, 0X88, 0x00); //set clock rate on VS1053 (Decoder) read opcode
    writeReg(0x0B, volume, volume); //set volume of VS1053 (Decoder)

    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
    xTaskCreate(readSD, "readSD", 512, ( void * ) 'A', 1, &readSDHandle );
    xTaskCreate(sendMP3, "sendMP3", 512, ( void * ) 'A', 3, &sendMP3Handle );
	xTaskCreate(controller, "controller", 512, (void * ) 'A', 2, NULL);
    
    scheduler_start();
    return -1;
}

void gpioInit()
{
    LPC_PINCON->PINSEL0 &= ~(3 << 2); // P0.1 DREQ
    LPC_PINCON->PINSEL0 &= ~(3 << 0); // P0.0 SDCS
    LPC_PINCON->PINSEL1 &= ~(3 << 26); // P0.29 XCS
    LPC_PINCON->PINSEL1 &= ~(3 << 28); // P0.30 XDCS
    LPC_PINCON->PINSEL4 &= ~(3 << 12); // P2.6 VS1053 rst

    LPC_GPIO0->FIODIR &= ~(1 << 1); // P0.1 DREQ input
    LPC_GPIO0->FIODIR |= (1 << 0); // P0.0 SD CS output
    LPC_GPIO0->FIODIR |= (1 << 29); // P0.29 XCS output
    LPC_GPIO0->FIODIR |= (1 << 30); // P0.30 XDCS output
    LPC_GPIO2->FIODIR |= (1 << 6); // P2.6 reset output
}

void writeReg(uint8_t address, uint8_t high, uint8_t low)
{
    while (myMP3.checkDREQ() == 0);
    myMP3.selectCS();
    mySPI.sendByte(0x02); //write opcode
    mySPI.sendByte(address);
    mySPI.sendByte(high);
    mySPI.sendByte(low);
    myMP3.deselectCS();
    while (myMP3.checkDREQ() == 0);
}

void suspendSendMP3_task() 
{
	vTaskSuspend(sendMP3Handle);
}
void resumeSendMP3_task() 
{
	vTaskResume(sendMP3Handle);
}





