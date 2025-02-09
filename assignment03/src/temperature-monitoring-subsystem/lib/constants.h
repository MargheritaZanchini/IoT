#pragma once

namespace Constants {
    constexpr const char* SSID = "TIM-29820711";
    constexpr const char* PASSWORD = "casa2020";

    constexpr const char* MQTT_SERVER = "broker.mqtt-dashboard.com";
    constexpr const char* MQTT_TEMPERATURE_TOPIC = "a03temperature";
    constexpr const char* MQTT_FREQUENCY_TOPIC = "a03frequency";
    constexpr const int MQTT_PORT = int(1883);

    constexpr const char* CLIENT_ID = "a03";

    constexpr const int RECONNECTION_INTERVAL = int(3000);
    constexpr const int BAUD_RATE = int(115200);

    constexpr const int MESSAGE_MAX_BUFFER = int(75);

    constexpr const int LED_OK_PIN = int(4);
    constexpr const int LED_ERROR_PIN = int(5);
    constexpr const int THERMISTOR_PIN = int(15);
}