#include "mqtt.h"

/**
 * Callback function for the MQTT connection.
 * 
 * @param topic The topic of the message
 * @param payload The message payload
 * @param length The length of the message
 * 
 * @return void
 * 
 * @note Created locally to avoid casting error inside client.setCallback.
 * Cannot cast void to std::function<void (char *, uint8_t *, unsigned int)>
 */
/*
 void callback(const char* topic, const byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    for(int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }

    Serial.println();
}
*/

/**
 * Constructor for the MQTT class.
 * 
 * @param espClient The WiFi client
 * @param client The PubSubClient
 */
MQTT::MQTT(WiFiClient espClient, PubSubClient client) {
    _espClient = espClient;
    _client = client;

    Serial.println("Setting up the WiFi connection...");
    setupWifi();

    Serial.println("Setting up the MQTT connection...");
    _client.setServer(Constants::MQTT_SERVER, Constants::MQTT_PORT);
    //_client.setCallback(callback);

    Serial.println("MQTT connected");
}

/**
 * Check if the device is OK, by checking if it is connected
 * to the WiFi and MQTT, and if it is sending data.
 * 
 * @return bool
 */
bool MQTT::isOK() {
    return isConnected() && isSendingData();
}

/**
 * Send the temperature to the MQTT broker.
 * 
 * @param temperature The temperature to send
 * 
 * @return void
 */
void MQTT::sendTemperature(float temperature) {
    snprintf(_message, Constants::MESSAGE_MAX_BUFFER, "temperature:%f", temperature);
    _lastMessageSent = _client.publish(Constants::MQTT_TEMPERATURE_TOPIC, _message);
}

/**
 * Setup the WiFi connection.
 * 
 * @return void
 */
void MQTT::setupWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(Constants::SSID, Constants::PASSWORD);

    while(WiFi.status() != WL_CONNECTED) { }
}

/**
 * Reconnect function for the MQTT.
 * 
 * @return void
 */
void MQTT::reconnect() {
    while(!_client.connected()) {
        Serial.println("Connecting to MQTT...");

        if(_client.connect(Constants::CLIENT_ID)) {
            _client.subscribe(Constants::MQTT_TEMPERATURE_TOPIC);
            _client.subscribe(Constants::MQTT_FREQUENCY_TOPIC);

            Serial.println("Connected to the MQTT broker");
        }
        else {
            Serial.print("Error, retrying...");
            delay(Constants::RECONNECTION_INTERVAL);
        }
    }

    // _client.setCallback(callback);
    Serial.println("MQTT fully connected");
}

/**
 * Check if the device is connected to the WiFi and MQTT.
 * 
 * @return bool
 */
bool MQTT::isConnected() {
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Not Available");
        return false;
    }
    if(!_client.connected()) {
        Serial.println("Cannot connect to MQTT");
        return false;
    }

    return true;
}

/**
 * Check if the device is sending data, by checking the last message sending status.
 * 
 * @return bool
 */
bool MQTT::isSendingData() {
    return _lastMessageSent;
}