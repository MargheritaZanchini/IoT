#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>

#include "Thermistor.h"
#include "mqtt.h"
#include <TemperatureMonitoring.h>
#include <Led.h>

#include "../lib/constants.h"



WiFiClient espClient;
PubSubClient client(espClient);

Led* okLED; /** [Pointer] OK Indicator LED */
Led* errorLED; /** [Pointer] Error Indicator LED */

Thermistor* thermistor; /** [Pointer] Thermistor Sensor */

MQTT* mqtt; /** [Object] MQTT Communication */

TemperatureMonitoring* temperatureTask; /** [Pointer] Temperature Detection Task */

TaskHandle_t temperatureTaskHandle;



void temperatureMonitoringTask(void* parameter) {
    TickType_t xLastWakeTime;
    TickType_t xFrequency = 5000 / portTICK_PERIOD_MS;
    for ( ;; ) {
        //xFrequency = temperatureTask->getPeriod() / portTICK_PERIOD_MS; // Converto da ms a ticks
        temperatureTask->tick();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void setup() {
    Serial.begin(Constants::BAUD_RATE);

    mqtt = new MQTT(espClient, client);
    okLED = new Led(Constants::LED_OK_PIN);
    errorLED = new Led(Constants::LED_ERROR_PIN);
    thermistor = new Thermistor(Constants::THERMISTOR_PIN);

    temperatureTask = new TemperatureMonitoring(thermistor, okLED, errorLED);

    xTaskCreatePinnedToCore(temperatureMonitoringTask, "temperatureTask", 10000, NULL, 1, &temperatureTaskHandle, 1);
}

void loop() {
    if(!mqtt->isConnected()) {
        mqtt->reconnect();
    }

    client.loop();
}