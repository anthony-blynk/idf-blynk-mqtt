# ESP32 IDF project with Blynk and MQTT

An example of using an ESP32 IDF project with Blynk and MQTT

Shows Wifi Provisioning, OTA firmware updates, and sending multiple datastream readings to Blynk using MQTT

- build and flash the project to an ESP32
- use the Blynk App to provision the device
- it will start publishing readings to Blynk

# Setup

This uses the Blynk component, and that has a dependency on the ESP32 Arduino IDF Component which will be installed automatically.

Clone this repo.

There are two sdkconfig setting that must be updated for the Blynk Library component to build cleanly.
- set CONFIG_FREERTOS_HZ=1000
- set CONFIG_ESP_TLS_PSK_VERIFICATION=y
(these are set in the committed sdkconfig file but if you use your own you must set these)

Then clone the Blynk library into the components folder:
```
mkdir components
cd components
git clone https://github.com/anthony-blynk/blynk-library.git
```

Now it should build cleanly.
