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
#include <stdio.h>
#include "tasks.hpp"
#include "utilities.h"
#include "io.hpp"
#include "LabSPI.hpp"

typedef union
{
    uint8_t byte;
    struct
    {
        uint8_t rdy1:       1;
        uint8_t comp:       1;
        uint8_t density:    4;
        uint8_t protect:    1;
        uint8_t page_size:  1;
    }__attribute__((packed));
}statReg1;

typedef union
{
    uint8_t byte;
    struct
    {
        uint8_t rdy1:       1;
        uint8_t :           1;
        uint8_t epe:        1;
        uint8_t :           1;
        uint8_t sle:        1;
        uint8_t ps2:        1;
        uint8_t ps1:        1;
        uint8_t es:         1;
    }__attribute__((packed));
}statReg2;



inline bool CHECK_BIT(int var, int pos)
{
    return (bool)(var & (1 << pos));
}

void vTaskCode(void * pvParameters)
{
    char c = (char)((uint32_t)pvParameters);
    while(1)
    {
        for(int i = 0; i < 16; i++)
        {
            for(int j = 1; j < 5; j++)
            {
                LE.set((5-j), CHECK_BIT(i,j-1));
            }
            LD.setNumber(i);
            // printf("(%c) Hello World 0x%X\n", c, i);
	    	vTaskDelay(1000);
        }
    }
}

int main(void)
{    
    LabSPI mySPI;

    char manID;
    char devID[2];
    char statusReg[2];

    statReg1 myStatReg1;
    statReg2 myStatReg2;

    mySPI.init(1, 7, 1, 8);
    
    mySPI.selectChip();
    //LPC_GPIO1->FIOPIN &= ~(1 << 29);    //chip select logic analyzer
    mySPI.transfer(0x9F);               //send request for device info
    manID = mySPI.transfer(0);          //read manufacture id
    devID[0] = mySPI.transfer(0);       //read byte 1 of device id
    devID[1] = mySPI.transfer(0);       //read byte 2 of device id
    //LPC_GPIO1->FIOPIN |= (1 << 29);     //deselect logic analyzer
    mySPI.deselectChip();

    printf("Manufacture ID: %u\n", manID);
    printf("Device ID byte 1: %u byte 2: %u\n", devID[0], devID[1]);
    
    mySPI.selectChip();
    mySPI.transfer(0xD7);
    myStatReg1.byte = mySPI.transfer(0);
    myStatReg2.byte = mySPI.transfer(0);
    mySPI.deselectChip();

    printf("Status register byte 1: %u, byte 2: %u", myStatReg1.byte, myStatReg2.byte);

    if(myStatReg1.rdy1)
    {
        printf("rdy1");
    }
    else if(!myStatReg1.rdy1)
    {
        printf("!rdy1");
    }
    
    
    //scheduler_add_task(new terminalTask(PRIORITY_HIGH));
	//xTaskCreate(vTaskCode, "vTaskCode", 512, ( void * ) 'A', tskIDLE_PRIORITY, NULL );
    // Alias to vSchedulerStart();
    //scheduler_start();

    return -1;
}
