// *** MAIN SETTINGS ***
// Replace this block with correct template settings.
// You can find it for every template here:
//
//   https://blynk.cloud/dashboard/templates

#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPL5GXJpWj64"
#define BLYNK_TEMPLATE_NAME "Demo1"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

#include <BlynkEdgent.h>
#include <blynk_task.h>

#include "esp_log.h"
static const char *TAG = "BLYNK_MAIN";

char blynk_mqtt_uri[64];
char blynk_token[34];
bool blynk_provisioned = false;

static void blynk_task(void *pvParameters) {

    initArduino();  // Initialize ESP32 Arduino core

    setup();        

    while(1) {
        loop();         
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void blynk_wait_till_provisioned(void)
{
    while (!blynk_provisioned) 
    {
        ESP_LOGI(TAG, "waiting for Blynk provisioning...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void blynk_init(void) {
    xTaskCreate(blynk_task, "blynk_task", 16382, NULL, 1, NULL);
    blynk_wait_till_provisioned();
}

void setup()
{

  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();

  Serial.println("version 7!");
}

void loop() {
  BlynkEdgent.run();

  if ( !blynk_provisioned && configStore.getFlag(CONFIG_FLAG_VALID) ) 
  {
    snprintf(blynk_mqtt_uri, 64, "mqtts://%s:8883", configStore.cloudHost);  
    memcpy(blynk_token, configStore.cloudToken, sizeof(configStore.cloudToken));
    Serial.printf("blynk_main: device provisioned, broker: %s\n", blynk_mqtt_uri);
    blynk_provisioned = true;
  }

  delay(10);
}
