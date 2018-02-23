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
 /*
#include <stdio.h>
#include "tasks.hpp"
#include "utilities.h"
#include "io.hpp"

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
    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
	xTaskCreate(vTaskCode, "vTaskCode", 512, ( void * ) 'A', tskIDLE_PRIORITY, NULL );
    // Alias to vSchedulerStart();
    scheduler_start();
    return -1;
}
*/

#include "FreeRTOS.h"
#include "task.h"
#include "uart0_min.h"

void vTaskOneCode(void * pvParameters)
{
    while(1)
    {
    	uart0_puts("aaaaaaaaaaaaaaaaaaaa");
    	vTaskDelay(100); // This sleeps the task for 100ms (because 1 RTOS tick = 1 millisecond)
    }
}

// Create another task and run this code in a while(1) loop
void vTaskTwoCode(void * pvParameters)
{
    while(1)
    {
    	uart0_puts("bbbbbbbbbbbbbbbbbbbb");
    	vTaskDelay(100);
    }
}

// You can comment out the sample code of lpc1758_freertos project and run this code instead
int main(int argc, char const *argv[])
{
    /// This "stack" memory is enough for each task to run properly
    const uint32_t STACK_SIZE = 1024;
    TaskHandle_t xHandle = NULL;
    const uint32_t tskA_PRIORITY = 1;
    const uint32_t tskB_PRIORITY = 2;

    xTaskCreate(vTaskOneCode, "vTaskOneCode", STACK_SIZE, ( void * ) 1, tskA_PRIORITY, &xHandle ); /* Fill in the rest parameters for this task */
    xTaskCreate(vTaskTwoCode, "vTaskTwoCode", STACK_SIZE, ( void * ) 1, tskB_PRIORITY, &xHandle ); /* Fill in the rest parameters for this task */

    /* Start Scheduler - This will not return, and your tasks will start to run their while(1) loop */
    vTaskStartScheduler();

    return 0;
}
