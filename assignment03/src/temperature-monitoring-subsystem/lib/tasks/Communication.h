#pragma once

#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>

#include "config.h"

/**
 * \brief Communication Helper Class
 */
class Communication {
public:
    /**
     * \brief Alias Type of Callback Function for MQTT Received Messages
     * 
     * \param char* Topic
     * \param uint8_t* Payload
     * \param unsigned_int Payload Length
     */
    typedef std::function<void (char *, uint8_t *, unsigned int)> CallbackFunction;

    /**
     * \brief Creates New Communication Instance
     * 
     * \param wifiClient WiFi Client Instance
     * \param mqtt MQTT Client Instance
     */
    Communication(WiFiClient* wifiClient, PubSubClient* mqtt);

    /**
     * \brief Initializes WiFi and MQTT Connection
     */
    void begin();

    /**
     * \brief Reconnects to the MQTT Server
     */
    void reconnect();

    /**
     * \brief Checks if the MQTT Client is Connected
     * 
     * \return Connection Status
     */
    bool connected();

    /**
     * \brief Sends a Message to the MQTT Server
     * 
     * \param message Message to Send
     * \return If message was sent successfully
     */
    bool sendMessage(const char* message);

    /**
     * \brief Sets the Callback Function for MQTT Messages
     * 
     * \param callback Callback Function
     * \see{CallbackFunction}
     */
    void setCallback(CallbackFunction callback);

private:
    WiFiClient* _client; /** WiFi Client Instance */
    PubSubClient* _mqtt; /** MQTT Client Instance */

    /**
     * \brief Initializes WiFi Connection
     */
    void setupWiFi();

    /**
     * \brief Initializes MQTT Connection
    */
    void setupMQTT();
};
