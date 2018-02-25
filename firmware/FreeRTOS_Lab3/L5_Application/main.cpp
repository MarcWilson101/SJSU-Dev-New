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
#include "uart0_min.h"  //uart0_puts("UH")
#include "LPC17xx.h"
#include "cstdint"
#include <stdlib.h>
#include <unistd.h>
#include "ADCDriver.hpp"



inline bool CHECK_BIT(int var, int pos)
{
    return (bool)(var & (1 << pos));
}

void vTaskCode(void * pvParameters)
{
    /*
    char c = (char)((uint32_t)pvParameters);
    ADCDriver frontSeat;
    uint8_t myPin = 3;
    frontSeat.adcInitBurstMode(3);
    frontSeat.adcSelectPin(myPin);
    unsigned long ADGDR_Read;
    int channel = 1;
    int currentResult;
    while(1)
    {
        vTaskDelay(1000);
        printf("Raw Voltage: %i/n", frontSeat.readADCRawByChannel(3));
    }
    */
    LPC_SC->PCONP |= (1 << 6);          //power the pwm
    
    LPC_PINCON->PINSEL4 |= 1;            //select PWM for p2.0 (01)
    LPC_PINCON->PINSEL4 &= ~(1 << 1);
    
    LPC_PWM1->TCR |= 1;                 //enable counter mode
    LPC_PWM1->TCR |= (1 << 2);          //PWM enable

    LPC_PWM1->MCR = (1 << 1);           //reset TC if it matches MR0

    LPC_PWM1->MR0 = 100;                //cycle time 
    LPC_PWM1->MR1 = 10;                 //duty cycle
    
    LPC_PWM1->LER = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);    //put new value into MR1 for next cycle
    
    LPC_SC->PCLKSEL0 &= ~(1 << 13);      //select clock = pckl/8 (11)
    LPC_SC->PCLKSEL0 |= (1 << 12);

    LPC_PWM1->PCR = (1 << 9);           //enable pwm output for pwm1
}


int main(void)
{
    /*
    LPC_SC->PCONP |= (1 << 7);          //power the pwm
    
    LPC_SC->PCLKSEL0 |= (1 << 13);      //select clock = pckl/8 (11)
    LPC_SC->PCLKSEL0 |= (1 << 12);

    LPC_PINCON->PINSEL4 |= 1;            //select PWM for p2.0 (01)
    LPC_PINCON->PINSEL4 &= ~(1 << 1);

    LPC_PWM1->MR0 = 100;                //cycle time 
    LPC_PWM1->MR1 = 90;                 //duty cycle

    LPC_PWM1->TCR |= 1;                 //enable counter mode
    LPC_PWM1->TCR |= (1 << 2);          //PWM enable

    LPC_PWM1->PR = 475;                   //set prescalar = 0?
    LPC_PWM1->MCR = (1 << 1);           //reset TC if it matches MR0

    LPC_PWM1->LER = (1 << 1);           //put new value into MR1 for next cycle

    LPC_PWM1->PCR = (1 << 9);           //enable pwm output for pwm1

    while(1){};
    */
    //while(1)
    //{
    //    printf("Raw Voltage: %i/n", frontSeat.readADCRawByChannel(3));
    //}

    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
	xTaskCreate(vTaskCode, "vTaskCode", 512, ( void * ) 'A', 1, NULL );
    // Alias to vSchedulerStart();
    scheduler_start();
    return -1;
}
