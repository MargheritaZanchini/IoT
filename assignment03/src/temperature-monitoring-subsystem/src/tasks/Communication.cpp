// filepath: /c:/Users/volpoh/Desktop/IoT/assignment03/src/temperature-monitoring-subsystem/src/tasks/communication.cpp

#include "communication.h"

#include "config.h"

Communication::Communication(WiFiClient* wifiClient, PubSubClient* mqtt) {
    _client = wifiClient;
    _mqtt = mqtt;
}

void Communication::begin() {
    setupWiFi();
    setupMQTT();

    reconnect();
}

void Communication::setupWiFi() {
    Serial.println("Setting up WiFi");

    WiFi.mode(WIFI_STA);
    WiFi.begin(CONFIG_SSID, CONFIG_PASSWORD);

    Serial.println("Connecting to WiFi");
    while(WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("WiFi Connected to IP: ");
    Serial.println(WiFi.localIP());
}

void Communication::setupMQTT() {
    Serial.println("Setting up MQTT");

    _mqtt->setServer(CONFIG_MQTT_SERVER, CONFIG_MQTT_PORT);

    Serial.println("MQTT Connected");
}

void Communication::reconnect() {
    Serial.println("Attempting to reconnect to MQTT...");
    while(!_mqtt->connected()) {
        if(_mqtt->connect(CONFIG_CLIENT_ID, CONFIG_MQTT_TOPIC, CONIFG_MQTT_QOS, true, "Disconnected from MQTT")) {
            Serial.println("Connected to MQTT");
            _mqtt->subscribe(CONFIG_MQTT_TOPIC, CONIFG_MQTT_QOS);
        }
        else {
            Serial.print("Failed: ");
            Serial.println(_mqtt->state());

            Serial.print("Retrying in ");
            Serial.print(CONFIG_RECONNECTION_INTERVAL/1000);
            Serial.println(" seconds");
            
            delay(CONFIG_RECONNECTION_INTERVAL);
        }
    }
}

bool Communication::connected() {
    return _mqtt->connected();
}

bool Communication::sendTemperature(const char* message) {
    return _mqtt->publish(CONFIG_MQTT_TOPIC, message);
}