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
#include "LPC17xx.h"

inline bool CHECK_BIT(int var, int pos)
{
    return (bool)(var & (1 << pos));
}

void vTaskCode(void * pvParameters)
{

    vTaskDelay(1000);
    uint32_t temp = 48000000 / (16 * 38400);
    LPC_SC->PCONP |= (1 << 25);                         //enable UART3

    LPC_SC->PCLKSEL1 &= ~(3 << 18);                     //clear
    LPC_SC->PCLKSEL1 |= (1 << 18);                      //set clock for UART3 = pclk/8 (01)
    
    LPC_PINCON->PINSEL9 |= (3 << 24) | (3 << 26);       //enable TXD3 and RXD3
    
    LPC_UART3->LCR = (1 << 7);                          //DLAB enable
    LPC_UART3->LCR = 3;                                 //8 bit transfer
    
    //LPC_UART3->FCR |= (1 << 0);                         //enable the fifo for uart

    LPC_UART3->DLL = temp;                              //setting baud rate
    LPC_UART3->DLM = (temp >> 8);

    LPC_UART3->LCR &= ~(1 << 7);                        //DLAB disable
    char data;
    while(1)
    {
        //vTaskDelay(1000);
        //LPC_UART3->THR = 'a';

        //while(!(LPC_UART3->LSR & (1 << 5))){}       //wait for end of transmission
        //printf("Sent a");
        //vTaskDelay(100000);
        
        //char data;
        //while(1)
        //{
        //    if(LPC_UART3->LSR & (1 << 0))
        //    {
        //        break;
        //    }
        //}
        printf("recieveing");
        while(! (LPC_UART3->LSR & (1 << 0)));
        data = LPC_UART3->RBR;
        printf("Data: %c\n", data);
        
    }

}

int main(void)
{
    uint32_t temp = 48000000 / (16 * 38400);
    LPC_SC->PCONP |= (1 << 25);                         //enable UART3

    LPC_SC->PCLKSEL1 &= ~(3 << 18);                     //clear
    LPC_SC->PCLKSEL1 |= (1 << 18);                      //set clock for UART3 = pclk/8 (01)
    
    LPC_PINCON->PINSEL9 |= (3 << 24) | (3 << 26);       //enable TXD3 and RXD3
    
    LPC_UART3->LCR = (1 << 7);                          //DLAB enable
    LPC_UART3->LCR = 3;                                 //8 bit transfer
    
    LPC_UART3->FCR |= (1 << 0);                         //enable the fifo for uart

    LPC_UART3->DLL = temp;                              //setting baud rate
    LPC_UART3->DLM = (temp >> 8);

    LPC_UART3->LCR &= ~(1 << 7);                        //DLAB disable

    char data;

        //vTaskDelay(1000);
        LPC_UART3->THR = 'a';
        while(!(LPC_UART3->LSR & (1 << 5))){}       //wait for end of transmission
        printf("Sent a");
        //vTaskDelay(100000);
          while(1)
    {  
        while(1)
        {
            if(LPC_UART3->LSR & (1 << 0))
            {
                break;
            }
        }
        //printf("recieveing");
        while(! (LPC_UART3->LSR & (1 << 0)));
        data = LPC_UART3->RBR;
        printf("Data: %c\n", data);
        
    }

    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
	xTaskCreate(vTaskCode, "vTaskCode", 512, ( void * ) 'A', tskIDLE_PRIORITY, NULL );
    // Alias to vSchedulerStart();
    scheduler_start();
    return -1;
}
