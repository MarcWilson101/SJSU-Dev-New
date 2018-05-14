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
#include "i2c2.hpp"

//LCD

#define LCD_ADDR 0x4E
#define LINE1 0x80
#define LINE2 0xC0
#define CLEAR 0x01

void sendLCDCommand(uint8_t command);
void sendSongName(char* songName, uint8_t nameLength);
void sendString(char string[]);			//
void sendCharacter(uint8_t character);
void init4Bit();
void writeVolumeLCD(uint8_t volume);



void tx(void *p)
{
	//init4Bit();
    char playlist[1][19] = {"1:track001.mp3"};
	uint8_t tracknumber = 0;
	char *songNamePtr = *(playlist + tracknumber);
    while(1)
    {
        vTaskDelay(5000);
        sendLCDCommand(CLEAR);
		vTaskDelay(1000);
		sendSongName(songNamePtr, 19);
		writeVolumeLCD(10);
    }
}

int main(void)
{
    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
    xTaskCreate(tx, "tx", 512, ( void * ) 'A', PRIORITY_HIGH, NULL );
    
    // Alias to vSchedulerStart();
    scheduler_start();
    return -1;
}


//sending commands to LCD (adjusting settings)
void sendLCDCommand(uint8_t command) {
	I2C2& master = I2C2::getInstance();
	master.init(100000);

	uint8_t sendCommand[4];
	uint8_t* ptr = sendCommand;
	uint8_t upperbit = command & 0xF0;
	uint8_t lowerbit = (command << 4) & 0xF0;

	sendCommand[0] = upperbit | 0x0C;
	sendCommand[1] = upperbit | 0x08;
	sendCommand[2] = lowerbit | 0x0C;
	sendCommand[3] = lowerbit | 0x08;

	for (int i = 0; i < 4; i++) {
		master.writeRegisters(LCD_ADDR, ptr, 1);
		ptr++;
//		vTaskDelay(50);
	}
}

//send characters to LCD 
void sendCharacter(uint8_t character) {
	I2C2& master = I2C2::getInstance();
	master.init(100000);

	uint8_t sendLetter[4];
	uint8_t* ptr = sendLetter;
	uint8_t upperbit = character & 0xF0;
	uint8_t lowerbit = (character << 4) & 0xF0;

	sendLetter[0] = upperbit | 0x0D;
	sendLetter[1] = upperbit | 0x09;
	sendLetter[2] = lowerbit | 0x0D;
	sendLetter[3] = lowerbit | 0x09;

	for (int i = 0; i < 4; i++) {
		master.writeRegisters(LCD_ADDR, ptr, 1);
		ptr++;
//		vTaskDelay(50);
	}
}

//print volume to LCD screen
void writeVolumeLCD(uint8_t volume)
{
	I2C2& master = I2C2::getInstance();
	master.init(100000);

	volume = 15 - (volume / 16); // Volume 0x4E = 11 on volume scale of 1-15

	char volumeUp = (char)((volume / 10) +'0'); // MSB of volume
	char volumeLow = (char)((volume % 10) + '0'); // LSB of volume

//	u0_dbg_printf("\nWrite Volume up: %x", volumeUp);
//	u0_dbg_printf("\nWrite Volume low: %x", volumeLow);
	sendLCDCommand(LINE2);
	char arr[] = "Vol:";
	sendString(arr);
	sendCharacter(volumeUp);
	sendCharacter(volumeLow);
}

void sendString(char string[]){
	char* ptr = string;
	//sendLCDCommand(LINE1);
	for (int i = 0; i < strlen(string); i++, ptr++) {
			sendCharacter(*ptr);
//			u0_dbg_printf("\n%c", *ptr);
		}
}

//print song name to LCD screen (need ptr to song name and length of song name)
void sendSongName(char* songName, uint8_t nameLength) {
	char* ptr = songName;
	sendLCDCommand(LINE1);
	ptr++;
	for (int i = 0; i < nameLength - 2; i++, ptr++) {
		sendCharacter(*ptr);
	}

}

//Used to initalize the LCD in 4 bit mode when using the I2C backpack
void init4Bit() {
	I2C2& master = I2C2::getInstance();
	master.init(10000);

	sendLCDCommand(0x03);
	//vTaskDelay(5);
	sendLCDCommand(0x03);
	//vTaskDelay(5);
	sendLCDCommand(0x03);
	//vTaskDelay(5);
	sendLCDCommand(0x02);
	sendLCDCommand(0x0F);

}