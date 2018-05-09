
#include <stdio.h>
#include "i2c2.hpp"
#include "LCD.hpp"

#define LCD_ADDR 0x4E
#define LINE1 0x80
#define LINE2 0xC0
#define CLEAR 0x01

/**
 * 1) sets up i2c instance 
 * 2) sends character to be printed to lcd screen
 *
 * @param character . character to be printed
*/
void LCD::LCDsendChar(uint8_t character)
{
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
	}
}

/**
 * 1) sets up i2c connection to LCD
 * 2) sends a command to the LCD. example: 0x01 CLEAR
 *
 * @param command . In hex format for the LCD screen
 */
void LCD::LCDsendCommand(uint8_t command)
{
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
	}
}

/**
 * 1) sends song name to be printed to lcd screen by calling LCDsendChar
 *
 * @param songName . Name of the song to be printed
 * @param nameLength . length of the name of the song. Will all be same length to make easier
 */
void LCD::LCDsendSongName(char* songName, uint8_t nameLength)
{
	char* ptr = songName;
	LCDsendCommand(LINE1);
	ptr++;
	for (int i = 0; i < nameLength - 2; i++, ptr++) {
		LCDsendChar(*ptr);
	}
}

/**
 * 1) sends string to be printed to lcd screen by calling LCDsendChar
 *
 * @param string[] . string to be printed
*/
void LCD::LCDsendString(char string[])
{
	char* ptr = string;
	LCDsendCommand(LINE1);
	for (int i = 0; i < strlen(string); i++, ptr++) {
			LCDsendChar(*ptr);
	}
}

/**
 * 1) sets up i2c instance 
 * 2) sets up LCD to be in 4 bit mode with the i2c backpack
*/
void LCD::LCDinit()
{
	I2C2& master = I2C2::getInstance();
	master.init(10000);
	LCDsendCommand(0x03);
	LCDsendCommand(0x03);
	LCDsendCommand(0x03);
	LCDsendCommand(0x02);
	LCDsendCommand(0x0F);
	LCDsendCommand(CLEAR);
}

/**
 * 1) sends volume to lcd screen
 * 
 * @param volume . volume to be printed to screen
*/
void LCD::LCDsendVolume(uint8_t volume)
{
	I2C2& master = I2C2::getInstance();
	master.init(100000);

	volume = 15 - (volume / 16); // Volume 0x4E = 11 on volume scale of 1-15

	char volumeUpper = (char)((volume / 10) +'0'); // MSB of volume
	char volumeLower = (char)((volume % 10) + '0'); // LSB of volume

	LCDsendCommand(LINE1);
	char vol[] = "Volume:";
	LCDsendString(vol);
	LCDsendChar(volumeUpper);
	LCDsendChar(volumeLower);
}

LCD::LCD(){}
LCD::~LCD(){}

/*
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
	char arr[] = "Volume:";
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
	sendLCDCommand(0x03);
	sendLCDCommand(0x03);
	sendLCDCommand(0x02);
	sendLCDCommand(0x0F);

}
*/