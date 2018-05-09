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

//GPIO and SPI functions
uint8_t sendByte(uint8_t out);
bool checkDREQ();
void selectCS();
void deselectCS();
void selectDCS();
void deselectDCS();
uint16_t readReg(uint8_t address);
void writeReg(uint8_t address, uint8_t high, uint8_t low);
void volumeUp();
void volumeDown();
void volumeMute();

//typedef enum {
//	mp3_queue,
//} sharedHandleId_t;

typedef enum {
	previous, next
} playBack_t;

/*GLOBALS*/
char playlist[1][19] = { "1:track001.mp3" };
char (*nowPlaying)[19] = &playlist[0];
uint8_t trackNumber = 0;
uint8_t volumeUpper = 0x4E;
uint8_t volumeLower = 0x4E;
bool isPlaying = true;
bool mute = false;
LCD myLCD;
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
QueueHandle_t my_queue = xQueueCreate(3, sizeof(uint8_t*));
void readMP3(void *p)
{
	u0_dbg_printf("-----In readMP3 task-------");
//QueueHandle_t my_queue = xQueueCreate(1, sizeof(uint8_t*));
//		addSharedObject(mp3_queue, my_queue);

    /*Power on SSP0*/
    LPC_SC->PCONP |= (1 << 21);

    /*Set clock rate for SSP0*/
    LPC_SC->PCLKSEL1 &= ~(3 << 10); //clear bits
    LPC_SC->PCLKSEL1 |= (1 << 10); // 01 set to CPU = CLK/1 (48MHz)

    /*Configure SSP0 pins SCK, MISO, MOSI*/
    LPC_PINCON->PINSEL0 &= ~(3 << 30); //P0.15 SCK0
    LPC_PINCON->PINSEL0 |= (1 << 31);
    LPC_PINCON->PINSEL1 &= ~(3 << 2);  //P0.17 MISO0
    LPC_PINCON->PINSEL1 |= (1 << 3);
    LPC_PINCON->PINSEL1 &= ~(3 << 4);  //P0.18 MOSI0
    LPC_PINCON->PINSEL1 |= (1 << 5);

    /*Clock prescaler*/
    LPC_SSP0->CPSR = 0; // SCK = CPU/2 = 24MHz

    /*Data size select for 8-bit transfer*/
    LPC_SSP0->CR0 = 7;

    /*Enable SSP*/
    LPC_SSP0->CR1 |= (1 << 1);

    /*Enable as SSP master*/
    LPC_SSP0->CR1 &= ~(1 << 2);

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

    /*Deassert pins*/
    deselectCS();	// deselect chip select signal of VS1053
    deselectDCS();	// deselect DATA chip select signal of VS1053
    LPC_GPIO0->FIOPIN |= (1 << 0);
    LPC_GPIO2->FIOPIN |= (1 << 6);


    writeReg(0x03, 0X88, 0x00); //set clock rate on VS1053 (Decoder) read opcode
    writeReg(0x0B, volumeUpper, volumeLower); //set volume of VS1053 (Decoder)

	while(1)
    {
//		vTaskDelay(1000);
//
		u0_dbg_printf("-------Read mp3task while------");
		//		FILE *file = fopen("1:track001.mp3", "r");
		//		size_t amount = 512;

		bool fileOpen;
		playBack_t playBackState = next;

		char *SDbuffer;
		SDbuffer = (char*) malloc(sizeof(char) * 512);
//		u0_dbg_printf("---------Here???????-------");
		FILE *file = fopen("1:track003.mp3", "r");
		if (file != NULL)
		{
			fileOpen = true;
			u0_dbg_printf("---------file is open-------");
		}
		else
			u0_dbg_printf("---------failed to open file--------");

		/* Gets the file size by offsetting the position indicator of the file stream to the end of file.
		 * Resets position back to beginning of the file.
		 */
		//u0_dbg_printf("---------Here?-------");

		fseek(file, 0, SEEK_END);
		//u0_dbg_printf("---------Here?-------");
		int fileSize = ftell(file);
		//u0_dbg_printf("---------Here??????-------");
		fseek(file, 0, SEEK_SET);
//		rewind(file);

		//u0_dbg_printf("-----Track Number: %i -------", trackNumber);
		/*Clear and write track name to display*/
		myLCD.LCDsendCommand(CLEAR);
		myLCD.LCDsendVolume(volumeUpper);

		/* Reads and sends from SD card in 512byte blocks. Sends this block of data to the sendMP3 task's queue.
		 * This task also handles semaphores sent from the controller task.
		 */

		//while loop reads data from buffer (512 bytes at a time) and sends to Decoder
		while (fileOpen) 
		{
			//u0_dbg_printf("File is open");
			for (int i = 0; i < fileSize; i = i + 512) 
			{
				//u0_dbg_printf("--------- Fread ----------- %u", i);
				fread(SDbuffer, 1, (size_t) 512, file); // Read 32byte block from SD
				xQueueSend(my_queue, &SDbuffer, portMAX_DELAY);
			} // end for loop
			fclose(file);
			fileOpen = false;
		}
		free(SDbuffer);
	}
}
//QueueHandle_t queueName = my_queue;
void sendMP3(void *p)
{
	//u0_dbg_printf("-------Send task-------");

	volumeUp();



    uint8_t *mp3ptr;
	uint16_t x = 0;
	while(1)
    {
		x = 0;
		//QueueHandle_t queueName = mp3_queue;
		//u0_dbg_printf("---------qreceive---------");
		if (xQueueReceive(my_queue, &mp3ptr, portMAX_DELAY)) { // While sending to decoder, poll for pause button and give semaphore to controller task below
			/* Start sending data to the decoder. When the decoder is ready(DREQ is HIGH), assert data chip select
			 * send 32 bytes to the decoder, then deassert data chip select. Continue until all 512 bytes are sent
			 */
			while (x < 512) {
				//u0_dbg_printf("---------checkDREQ---------");
				while (checkDREQ() == 0);
				selectDCS();
				//u0_dbg_printf("-------after selecting DCS task---------\n");			
				for (uint8_t i = 0; i < 32; i++, mp3ptr++, x++) 
				{
					//u0_dbg_printf("-------inside for loop---------\n");			
				
					//u0_dbg_printf("------Send %x: -----\n", *mp3ptr);
					sendByte(*mp3ptr);
					//x++;
					//mp3ptr++;
				}
				//u0_dbg_printf("-------fter selecting DCS task---------\n");			
				while (checkDREQ() == 0);
				deselectDCS();
			} // end while loop
		}
    }


}


int main(void)
{
	myLCD.LCDinit();
	char songptr[] = "what if this is really long";
    myLCD.LCDsendString(songptr);
	myLCD.LCDsendCommand(CLEAR);
	myLCD.LCDsendCommand(LINE1);

	myLCD.sendCommand(LINE2);

    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
    //xTaskCreate(LCDWrite, "LCDWrite", 512, ( void * ) 'A', 4, NULL );
    xTaskCreate(readMP3, "readMP3", 512, ( void * ) 'A', 2, NULL );
    xTaskCreate(sendMP3, "sendMP3", 512, ( void * ) 'A', 1, NULL );
    
    // Alias to vSchedulerStart();
    scheduler_start();
    return -1;
}

/*SJOne GPIO and SPI*/
uint8_t sendByte(uint8_t out) {
	LPC_SSP0->DR = out;
	while (LPC_SSP0->SR & (1 << 4))
		; // wait while the SSP controller is busy bit = 1, idle = 0
	return LPC_SSP0->DR;
}
bool checkDREQ() {
	if (LPC_GPIO0->FIOPIN & (1 << 1)) {
		return true;
	} else
		return false;
}
void selectCS() {
		//u0_dbg_printf("-----Select CS------");
	LPC_GPIO0->FIOCLR |= (1 << 29);
}
void deselectCS() {
		//u0_dbg_printf("-----Deselect CS-----");
	LPC_GPIO0->FIOSET |= (1 << 29);
}
void selectDCS() {
		//u0_dbg_printf("-----Select DCS------");
	LPC_GPIO0->FIOCLR |= (1 << 30);
}
void deselectDCS() {
		//u0_dbg_printf("-----Deselect DCS----");
	LPC_GPIO0->FIOSET |= (1 << 30);
}
uint16_t readReg(uint8_t address) {
	//u0_dbg_printf("\n\nREAD FROM REGISTER");
	while (checkDREQ() == 0)
		;
	selectCS();

	//u0_dbg_printf("\nSend opcode: %x", sendByte(0x03));
	//u0_dbg_printf("\nSend register address: %x", sendByte(address));
	sendByte(0x03);
	sendByte(address);

	uint8_t response1 = sendByte(0XFF); // Read first byte
	while (checkDREQ() == 0)
		;
	vTaskDelay(10);
	uint8_t response2 = sendByte(0XFF); // Read second byte
	while (checkDREQ() == 0)
		;

	//u0_dbg_printf("\nByte 1: %x", response1);
	//u0_dbg_printf("\nByte 2: %x", response2);

	deselectCS();
	uint16_t result = response1 << 8;
	result |= response2;
	//u0_dbg_printf("\nResult: %x", result);
	return result;
}

void writeReg(uint8_t address, uint8_t high, uint8_t low) {
		u0_dbg_printf("------WRITE TO REGISTER------");
	while (checkDREQ() == 0);
	selectCS();
//		u0_dbg_printf("\nSend opcode: %x, %x", WRITE_OPCODE, exchangeByte(WRITE_OPCODE));
//		u0_dbg_printf("\nSend register address: %x, %x", address, exchangeByte(address));
//		u0_dbg_printf("\nWrite byte 1: %x %x", high, exchangeByte(high));
//		u0_dbg_printf("\nWrite byte 2: %x %x", low, exchangeByte(low));

	sendByte(0x02); //write opcode
	sendByte(address);
	sendByte(high);
	sendByte(low);

	deselectCS();
	while (checkDREQ() == 0);

}

//Task suspend/resume
void suspendSendMP3_task() {
//	u0_dbg_printf("\nSuspending sendmp3_task");
	vTaskSuspend(
			scheduler_task::getTaskPtrByName("sendmp3_task")->getTaskHandle());
}
void resumeSendMP3_task() {
	u0_dbg_printf("\nResuming sendmp3_task");
	vTaskResume(
			scheduler_task::getTaskPtrByName("sendmp3_task")->getTaskHandle());
}
void volumeUp() {
	mute = false;
	if(volumeUpper != 0x0E){
		volumeUpper -= 0x10;
		volumeLower -= 0x10;
		writeReg(0x0B, volumeUpper, volumeLower);
	}
	myLCD.LCDsendVolume(volumeUpper);
}
void volumeDown() {
	mute = false;
	if (volumeUpper != 0xFE) {
		volumeUpper += 0x10;
		volumeLower += 0x10;
		writeReg(0x0B, volumeUpper, volumeLower);
	}
	myLCD.LCDsendVolume(volumeUpper);
}
void volumeMute(){
	if (mute) {
		u0_dbg_printf("\nUnmuting.");
		writeReg(0x0B, volumeUpper, volumeLower);
	} else {
		u0_dbg_printf("\nMuting.");
		writeReg(0x0B, 0xFE, 0xFE);
	}
	mute = !mute;
}



