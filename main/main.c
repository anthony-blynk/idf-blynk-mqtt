#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include <blynk_task.h>
#include <mqtt.h>
#include "cJSON.h"

static const char *TAG = "IDFBLYNKMQTT";

int someDS1 = 0;
int someDS2 = 0;

void send_data(void)
{
    someDS1 += 1;
    someDS2 += 2;

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "Some1", someDS1);
    cJSON_AddNumberToObject(root, "Some2", someDS2);
    char *json_string = cJSON_Print(root);
    cJSON_Delete(root); 

    mqtt_publish("batch_ds", json_string);
}

// these are from blynk_main.cc
extern char blynk_mqtt_uri[64];
extern char blynk_token[34];

void app_main(void)
{
    ESP_LOGI(TAG, "app_main start");

    blynk_init(); 

    mqtt_init(blynk_mqtt_uri, blynk_token);

    while (1) {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        send_data();
    }
}
