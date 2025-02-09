#pragma once

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#include "../lib/constants.h"

class MQTT {
public:
    MQTT(WiFiClient espClient, PubSubClient client);

    void sendTemperature(float temperature);
    void reconnect();

    bool isOK();
    bool isConnected();
    bool isSendingData();

private:
    WiFiClient _espClient;
    PubSubClient _client;

    char _message[Constants::MESSAGE_MAX_BUFFER];
    bool _lastMessageSent = false;

    void setupWifi();
};
