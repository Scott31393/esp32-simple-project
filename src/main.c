#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main()
{
    int counter = 0;
    while(1){
        vTaskDelay(1000/portTICK_PERIOD_MS);
        printf("Counter = %d \n", ++counter);
    }
}