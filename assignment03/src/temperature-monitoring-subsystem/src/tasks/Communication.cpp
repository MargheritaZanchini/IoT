#include "communication.h"

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

    WiFi.mode(WIFI_STA); // Set WiFi Mode to Station
    WiFi.begin(CONFIG_SSID, CONFIG_PASSWORD); // Connect to WiFi

    // Wait for WiFi Connection
    Serial.println("Connecting to WiFi");
    while(WiFi.status() != WL_CONNECTED) { 
        delay(100);
        Serial.print(".");
    }

    // Print WiFi Connection Information
    Serial.println();
    Serial.print("WiFi Connected to IP: ");
    Serial.println(WiFi.localIP());
}

void Communication::setupMQTT() {
    Serial.println("Setting up MQTT");

    _mqtt->setServer(CONFIG_MQTT_SERVER, CONFIG_MQTT_PORT); // Set MQTT Server and Port

    Serial.println("MQTT Connected");
}

void Communication::reconnect() {
    Serial.println("Attempting to reconnect to MQTT...");

    while(!_mqtt->connected()) { // While MQTT is not connected,
        if(_mqtt->connect(CONFIG_CLIENT_ID, CONFIG_MQTT_TOPIC, CONIFG_MQTT_QOS, true, "Disconnected from MQTT")) { // Try to connect to MQTT
            Serial.println("Connected to MQTT");
            _mqtt->subscribe(CONFIG_MQTT_TOPIC, CONIFG_MQTT_QOS); // and subscribe to the given MQTT Topic
        }
        else { // If Connection Failed,
            // Print the MQTT Error Code
            Serial.print("Failed: ");
            Serial.println(_mqtt->state());

            // and try to reconnect in the given interval
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

bool Communication::sendMessage(const char* message) {
    return _mqtt->publish(CONFIG_MQTT_TOPIC, message);
}

void Communication::setCallback(CallbackFunction callback) {
    _mqtt->setCallback(callback);
}
