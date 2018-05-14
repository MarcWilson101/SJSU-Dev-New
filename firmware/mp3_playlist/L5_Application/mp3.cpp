#include <mp3.hpp>
#include <LPC17xx.h>

void mp3::mp3Init()
{
    /*Deassert pins*/
    deselectCS();	// deselect chip select signal of VS1053
    deselectDCS();	// deselect DATA chip select signal of VS1053
    LPC_GPIO0->FIOPIN |= (1 << 0);
    LPC_GPIO2->FIOPIN |= (1 << 6);
}

bool mp3::checkDREQ()
{
    if (LPC_GPIO0->FIOPIN & (1 << 1)) 
    {
        return true;
    } 
    else
        return false;
}

void mp3::selectCS()
{
    LPC_GPIO0->FIOCLR |= (1 << 29);
}

void mp3::deselectCS()
{
    LPC_GPIO0->FIOSET |= (1 << 29);
}

void mp3::selectDCS()
{
    LPC_GPIO0->FIOCLR |= (1 << 30);
}

void mp3::deselectDCS()
{
    LPC_GPIO0->FIOSET |= (1 << 30);
}

