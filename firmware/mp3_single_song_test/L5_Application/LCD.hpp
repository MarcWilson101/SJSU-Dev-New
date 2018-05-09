
//#ifndef LCD_H
//#define LCD_H

#include <stdio.h>

#define LCD_ADDR 0x4E
#define LINE1 0x80
#define LINE2 0xC0
#define CLEAR 0x01


class LCD{

private:    


public:

    /**
     * 1) sets up i2c instance 
     * 2) sends character to be printed to lcd screen
     *
     * @param character . character to be printed
    */
    void LCDsendChar(uint8_t character);
    
    /**
     * 1) sets up i2c connection to LCD
     * 2) sends a command to the LCD. example: 0x01 CLEAR
     *
     * @param command . In hex format for the LCD screen
     */
    void LCDsendCommand(uint8_t command);

    /**
     * 1) sends song name to be printed to lcd screen by calling LCDsendChar
     *
     * @param songName . Name of the song to be printed
     * @param nameLength . length of the name of the song. Will all be same length to make easier
     */
    void LCDsendSongName(char* songName, uint8_t nameLength);

    /**
     * 1) sends string to be printed to lcd screen by calling LCDsendChar
     *
     * @param string[] . string to be printed
    */
    void LCDsendString(char string[]);

    /**
     * 1) sets up i2c instance 
     * 2) sets up LCD to be in 4 bit mode with the i2c backpack
    */
    void LCDinit();

    /**
     * 1) sends volume to lcd screen
     * 
     * @param volume . volume to be printed to screen
    */
    void LCDsendVolume(uint8_t volume);
    
    LCD();
    ~LCD();
};


//#endif