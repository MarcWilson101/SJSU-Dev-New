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
#include "UartDriver.hpp"


QueueHandle_t q = xQueueCreate(50, sizeof(char));
UartDriver *myUart3 = new UartDriver();


void uart3RxInt()
{
    char data;
    data = myUart3->receiveChar();
    xQueueSendFromISR(q, &data, NULL);
    //clear interrupt flag
}

void vTaskCode(void * pvParameters)
{

    vTaskDelay(100);
    myUart3->transmitChar('1');
    vTaskDelay(100);
    myUart2->transmitChar('2');
    vTaskDelay(100);
    myUart3->transmitChar('+');

    char l, r, op;
    xQueueReceive(q, &l, 100); //dummy
    xQueueReceive(q, &l, 100);
    xQueueReceive(q, &r, 100);
    xQueueReceive(q, &op, 100);

    printf("left: %c\n", l);
    printf("right: %c\n", r);
    printf("op: %c\n", op);

    LD.setNumber(1);

    vTaskDelay(1000000000);

}

int main(void)
{
    isr_register(UART3_IRQn, uart3RxInt);
    myUart3->UartInit(3, 9600);
    //UartDriver myUart3;
    //myUart3.UartInit(3, 9600);

    //UartDriver *myUart2 = new UartDriver();
    //myUart2->UartInit(2, 9600);

    //char op, left, right;
    
    //uint8_t answer, l, r;

    //while(1)
    //{  
        //myUart3.putChar('a');      
        //dataA = myUart3.getChar();
        //printf("Received: %c\n", dataA);  

        //answer = myUart2->receiveChar();

        //myUart2->transmitChar('1');
        //left = myUart2->receiveChar();

        //myUart2->transmitChar('2');
        //right = myUart2->receiveChar();

        //myUart2->transmitChar('+');
        //op = myUart2->receiveChar();
        
        //printf("left: %c\n", left);
        //printf("right: %c\n", right);
        //printf("op: %c\n", op);
        
        //l = left - '0';
        //r = right - '0';
/*
        switch(op)
        {
            case '+':
                answer = l + r;
                break;
            case '-':
                answer = l - r;
                break;
            case '*':
                answer = l * r;
                break;
            case '/':
                answer = l * r;
                break;
            default:
                answer = l + r;
                break;

        }
*/
        //printf("Answer: %u\n", answer);
    //}
    
    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
	xTaskCreate(vTaskCode, "vTaskCode", 512, ( void * ) 'A', tskIDLE_PRIORITY, NULL );
    // Alias to vSchedulerStart();
    scheduler_start();
    return -1;
}
