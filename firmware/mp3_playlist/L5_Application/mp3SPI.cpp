#include <stdio.h>
#include <mp3SPI.hpp>
#include <LPC17xx.h>

    void mp3SPI::mp3SPIinit()
    {
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
    }


    uint8_t mp3SPI::sendByte(uint8_t out)
    {
        LPC_SSP0->DR = out;
	    while (LPC_SSP0->SR & (1 << 4)); // wait while the SSP controller is busy bit = 1, idle = 0
	    return LPC_SSP0->DR;
    }


    mp3SPI::mp3SPI(){}
    mp3SPI::~mp3SPI(){}