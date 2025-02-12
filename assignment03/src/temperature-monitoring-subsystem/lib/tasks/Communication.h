#pragma once

#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>

class Communication {
public:
    Communication(WiFiClient* wifiClient, PubSubClient* mqtt);

    void begin();
    void reconnect();

    bool connected();
    bool sendTemperature(const char* message);

private:
    WiFiClient* _client;
    PubSubClient* _mqtt;

    void setupWiFi();
    void setupMQTT();
};