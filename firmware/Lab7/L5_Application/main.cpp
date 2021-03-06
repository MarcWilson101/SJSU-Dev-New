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
#include "io.hpp"
#include "event_groups.h"
#include "ff.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "tasks.hpp"
#include <task.h>
#include <stdio.h>
#include "queue.h"

QueueHandle_t sensorQ = xQueueCreate(1000, sizeof(int));

EventGroupHandle_t xWatchDogEventGroup = xEventGroupCreate();
EventBits_t watchdogBits;

const char *pcNameToLookup1 = "vProducer";
//TaskHandle_t xProducerHandle = xTaskGetHandle( pcNameToLookup1 );

const char *pcNameToLookup = "vConsumer";
//TaskHandle_t xConsumerHandle = xTaskGetHandle( pcNameToLookup );

void vProducer(void * pvParameters)
{
    //char c = (char)((uint32_t)pvParameters);
    int sensorValues = 0;
    
    int avg = 0;

    while(1)
    {
        sensorValues = 0;
        for(int i = 0; i <=100; i++)
        {
            vTaskDelayMs(1);
            sensorValues += LS.getRawValue();
        }
        avg = sensorValues / 100;
        xQueueSend(sensorQ, ( void * ) &avg, portMAX_DELAY);
        //vTaskDelayMs(10000);
        watchdogBits = xEventGroupSetBits(xWatchDogEventGroup, (1 << 1));
        
    }
}

void vConsumer(void * pvParameters)
{
    //char c = (char)((uint32_t)pvParameters);
    int avg;
    int time;

    while(1)
    {
        vTaskDelayMs(100);
        xQueueReceive(sensorQ, &avg, portMAX_DELAY);
        time = xTaskGetTickCount();
        //printf("avg from q: %i\n", avg);
        FILE *fp = fopen("0:sensory.txt", "a+");
        fprintf(fp, "%i, %i\n", time, avg);
        fclose(fp);
        //vTaskDelayMs(10000);
        watchdogBits = xEventGroupSetBits(xWatchDogEventGroup, (1 << 2));
    }

}

void vWatchDog(void * pvParameter)
{
    const TickType_t xTicksToWait = 1000;
     
    while(1)
    {
        //printf("Checking for watchdog bits");
        watchdogBits = xEventGroupWaitBits(xWatchDogEventGroup, (1 << 1), pdTRUE, pdFALSE, xTicksToWait);
        watchdogBits = xEventGroupWaitBits(xWatchDogEventGroup, (1 << 2), pdTRUE, pdFALSE, xTicksToWait);
        if((watchdogBits & (1 << 1)) == 0)
        {
            FILE *fp1 = fopen("stuck.txt", "a+");
            fprintf(fp1, "Producer stuck\n" );
            fclose(fp1);
        }
        else if((watchdogBits & (1 << 2)) == 0)
        {
            FILE *fp2 = fopen("stuck.txt", "a+");
            fprintf(fp2, "Consumer stuck\n" );
            fclose(fp2);
        }
        //vTaskDelay(1000);
    }
}
/*
void vCPUStats(void * pvParameter)
{
    char *pcWriteBuffer;
    while(1)
    {
        vTaskDelayMs(1000);
        FILE *fp3 = fopen("cpu.txt", "a+");
        vTaskGetRunTimeStats( pcWriteBuffer );
        fprintf(fp3, "cpu info: %s", pcWriteBuffer);
        fclose(fp3);
    }
}
*/

int main(void)
{
    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
	xTaskCreate(vProducer, "vProducer", 512, ( void * ) 'A', 2, NULL );//&xProducerHandle );
    xTaskCreate(vConsumer, "vConsumer", 512, ( void * ) 'A', 2, NULL );//&xConsumerHandle );
    xTaskCreate(vWatchDog, "vWatchDog", 512, ( void * ) 'A', 1, NULL );
    //xTaskCreate(vCPUStats, "vCPUStats", 512, ( void * ) 'A', 1, NULL );
    

    // Alias to vSchedulerStart();
    scheduler_start();
    return -1;
}
