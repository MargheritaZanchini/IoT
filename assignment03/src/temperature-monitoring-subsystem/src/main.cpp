#include <Arduino.h>

#include "Communication.h"
#include "Monitoring.h"

#include "config.h"

Communication* communication;
Monitoring* monitoring;

void callback(char* topic, byte* payload, unsigned int length) {

}

void setup() {
    Serial.begin(CONFIG_BAUD_RATE);

    WiFiClient* wifiClient = new WiFiClient();
    PubSubClient* pubSubClient = new PubSubClient(*wifiClient);
    communication = new Communication(wifiClient, pubSubClient);

    communication->begin();

    monitoring = new Monitoring();
}

void loop() {
    // TO DO IN A TASK

    // float currentTemperature = monitoring->getTemperature();
    // String message = "temperature:" + String(currentTemperature);
    // communication->sendTemperature(message.c_str());

    delay(5000);
}