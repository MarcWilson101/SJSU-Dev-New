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

void writeReg(uint8_t address, uint8_t high, uint8_t low);
void volumeUp();
void volumeDown();
void gpioInit();

typedef enum {
	previous, next
} playBack_t;

/*GLOBALS*/
char playlist[3][19] = { "1:track001.mp3", "1:track002.mp3", "1:track003.mp3" };
uint8_t trackNumber = 0;
char (*nowPlaying)[19] = &playlist[trackNumber];
uint8_t volumeUpper = 0x4E;
uint8_t volumeLower = 0x4E;
bool isPlaying = true;
LCD myLCD;
mp3SPI mySPI;
mp3 myMP3;

/*
void LCDWrite(void *p)
{
	u0_dbg_printf("-------LCDWrite task--------");
    char songptr[] = "what if this is really long";
	
    //while(1)
    //{
       // vTaskDelay(5000);
        myLCD.LCDsendCommand(CLEAR);
		myLCD.LCDsendCommand(LINE1);
		//vTaskDelay(1000);
        myLCD.LCDsendString(songptr);
		u0_dbg_printf("-------should show on lcd-----");
		vTaskDelay(500000);
    //}
}
*/

void volume(void *p)
{
	ADCDriver myADC;
	myADC.adcInitBurstMode(3);
    myADC.adcSelectPin(3);
	float rawData;
	uint8_t oldVolumeUpper;
	uint8_t oldVolumeLower;
	uint8_t newVolumeUpper, newVolumeLower;


	while(1)
	{
		oldVolumeUpper = volumeUpper;
		oldVolumeLower = volumeLower;
		newVolumeUpper = 0;
		newVolumeLower = 0;

		//vTaskDelay(100);
		rawData = myADC.readADCRawByChannel(3);
		uint16_t intRawData = rawData; //cast it into an int..
		intRawData = intRawData * 2.5; //get 0-100 in 0-250 range
		newVolumeUpper |= intRawData >> 8;
		newVolumeLower |= intRawData;

		if(newVolumeUpper == oldVolumeUpper && newVolumeLower == oldVolumeLower)
		{
					//do nothing
		}
		else if(newVolumeUpper > oldVolumeUpper || newVolumeLower > oldVolumeLower)
		{
			volumeDown();
		}
		else if(newVolumeUpper < oldVolumeUpper || newVolumeLower < oldVolumeLower)
		{
			volumeUp();
		}
	}

}



QueueHandle_t my_queue = xQueueCreate(3, sizeof(uint8_t*));
void readMP3(void *p)
{
	while(1)
    {
		bool fileOpen;
		playBack_t playBackState = next;

		char *SDbuffer;
		SDbuffer = (char*) malloc(sizeof(char) * 512);
		FILE *file = fopen(*nowPlaying, "r");
		
		if (file != NULL)
			fileOpen = true;

		fseek(file, 0, SEEK_END);
		int fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);
		myLCD.LCDsendCommand(CLEAR);
		myLCD.LCDsendVolume(volumeUpper);

		//while loop reads data from buffer (512 bytes at a time) and sends to Decoder
		while (fileOpen) 
		{
			for (int i = 0; i < fileSize; i = i + 512) 
			{
				fread(SDbuffer, 1, (size_t) 512, file); // Read 32byte block from SD
				xQueueSend(my_queue, &SDbuffer, portMAX_DELAY);
			} // end for loop
			fclose(file);
			fileOpen = false;
		}
		free(SDbuffer);
		if(trackNumber != 3)
		{
			trackNumber++;
		}
		else
		{
			trackNumber = 0;
		}

	}
}

void sendMP3(void *p)
{
	volumeUp();

    uint8_t *mp3ptr;
	uint16_t x = 0;
	while(1)
    {
		x = 0;
		if (xQueueReceive(my_queue, &mp3ptr, portMAX_DELAY)) { 
			while (x < 512) {
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

int main(void)
{
	myLCD.LCDinit();
	mySPI.mp3SPIinit();
	gpioInit();
	myMP3.mp3Init(volumeUpper, volumeLower);

    writeReg(0x03, 0X88, 0x00); //set clock rate on VS1053 (Decoder) read opcode
    writeReg(0x0B, volumeUpper, volumeLower); //set volume of VS1053 (Decoder)

    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
    xTaskCreate(readMP3, "readMP3", 512, ( void * ) 'A', 2, NULL );
    xTaskCreate(sendMP3, "sendMP3", 512, ( void * ) 'A', 1, NULL );
	//xTaskCreate(volume, "volume", 512, (void * ) 'A', 1, NULL);
    
    // Alias to vSchedulerStart();
    scheduler_start();
    return -1;
}

/*SJOne GPIO and SPI*/
void gpioInit()
{
    /*Configure GPIO for DREQ(input), CS, DCS, Reset, SD-CS*/
    LPC_PINCON->PINSEL0 &= ~(3 << 2); // P0.1 DREQ input
    LPC_PINCON->PINSEL0 &= ~(3 << 0); // P0.0 SD CS output
    LPC_PINCON->PINSEL1 &= ~(3 << 26); // P0.29 XCS output
    LPC_PINCON->PINSEL1 &= ~(3 << 28); // P0.30 XDCS output
    LPC_PINCON->PINSEL4 &= ~(3 << 12); // P2.6 VS1053 reset output

    /*Configure input or output*/
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

void suspendSendMP3_task() {
	vTaskSuspend(
			scheduler_task::getTaskPtrByName("sendmp3_task")->getTaskHandle());
}
void resumeSendMP3_task() {
	u0_dbg_printf("\nResuming sendmp3_task");
	vTaskResume(
			scheduler_task::getTaskPtrByName("sendmp3_task")->getTaskHandle());
}
void volumeUp() 
{
	if(volumeUpper != 0x0E){
		volumeUpper -= 0x10;
		volumeLower -= 0x10;
		writeReg(0x0B, volumeUpper, volumeLower);
	}
	myLCD.LCDsendVolume(volumeUpper);
}
void volumeDown() 
{
	if (volumeUpper != 0xFE) {
		volumeUpper += 0x10;
		volumeLower += 0x10;
		writeReg(0x0B, volumeUpper, volumeLower);
	}
	myLCD.LCDsendVolume(volumeUpper);
}




