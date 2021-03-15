#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/task.h>

static QueueHandle_t xMainQueue = NULL;

typedef struct{
    char id;
    unsigned int arg;
}message_t;

typedef enum main_loop_events
{
    kMain_StartSTUFF0 = 0,
    kMain_StartSTUFF1,
    kMain_StartSTUFF2,
} main_loop_events_t;

static void main_equeue_msg(message_t msg2send)
{
    xQueueSend(xMainQueue, (void*) &msg2send, pdMS_TO_TICKS(100));
}

void main_send_evt(main_loop_events_t main_event)
{
    message_t msg2send;
    msg2send.id = main_event;
    msg2send.arg = 0;
    main_equeue_msg(msg2send);
}

void main_loop_task(void *pvParamters)
{
    xMainQueue = xQueueCreate(10, sizeof(message_t));
    message_t rx_msg;
    main_send_evt(kMain_StartSTUFF0);

    while(true)
    {
        memset(&rx_msg, 0, sizeof(message_t));
        if(xQueueReceive(xMainQueue, &rx_msg, pdMS_TO_TICKS(200)) == pdPASS)
        {
            switch(rx_msg.id)
            {
                case kMain_StartSTUFF0:
                    printf("Start stuff 0 \n");
                    break;

                case kMain_StartSTUFF1:
                    printf("Start stuff 1 \n");
                    break;

                case kMain_StartSTUFF2:
                    printf("Start stuff 2 \n");
                    break;

                default:
                    break;
            }
        }

    }

}

void app_main()
{
    xTaskCreate(main_loop_task, "main_loop_task", configMINIMAL_STACK_SIZE * 2, NULL, 1, NULL);
}