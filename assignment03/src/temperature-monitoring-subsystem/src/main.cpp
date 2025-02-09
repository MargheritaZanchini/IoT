#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>

#include "Thermistor.h"
#include <TemperatureMonitoring.h>
#include <Led.h>



const char* SSID = "TIM-29820711";
const char* PASSWORD = "casa2020";

const char* MQTT_SERVER = "broker.mqtt-dashboard.com";
const char* MQTT_TOPIC = "assignment03temperature";
const int MQTT_PORT = 1883;

const char* CLIENT_ID = "miao";

const int RECONNECTION_INTERVAL = 3000;
const int BAUD_RATE = 115200;

char msg[75];

WiFiClient espClient;
PubSubClient client(espClient);

Led* okLED; /** [Pointer] OK Indicator LED */
Led* errorLED; /** [Pointer] Error Indicator LED */

Thermistor* thermistor; /** [Pointer] Thermistor Sensor */

TemperatureMonitoring* temperatureTask; /** [Pointer] Temperature Detection Task */

TaskHandle_t temperatureTaskHandle;

void setupWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);

    while(WiFi.status() != WL_CONNECTED) { }
}

void callback(const char* topic, const byte* payload, unsigned int length) {

}

void reconnect() {
    while(!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if(client.connect(CLIENT_ID)) {
            Serial.println("Connected to the MQTT broker");
            client.subscribe(MQTT_TOPIC);
        } else {
            Serial.print("Error, retrying...");
            delay(RECONNECTION_INTERVAL);
        }
    }

    Serial.println("MQTT connected, adding callback function...");
    client.setCallback(callback);
}

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
    Serial.begin(BAUD_RATE);

    Serial.println("Setting up the WiFi connection...");
    setupWifi();
    Serial.println("WiFi connected");

    Serial.println("Setting up the MQTT connection...");
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);
    Serial.println("MQTT connected");

    okLED = new Led(4);
    errorLED = new Led(5);
    thermistor = new Thermistor(15);

    temperatureTask = new TemperatureMonitoring(thermistor, okLED, errorLED);

    xTaskCreatePinnedToCore(temperatureMonitoringTask, "temperatureTask", 10000, NULL, 1, &temperatureTaskHandle, 1);
}

void loop() {
    if(!client.connected()) {
        reconnect();
    }

    client.loop();

    randomSeed(micros());
    snprintf(msg, 75, "Temperature: %d", random(0, 100));
    
    Serial.println(String("Publishing message ... ") + msg);

    client.publish(MQTT_TOPIC, msg);

    delay(5000);
}