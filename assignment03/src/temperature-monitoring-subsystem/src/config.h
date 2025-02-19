#pragma once

#define CONFIG_SSID "TIM-29820711" /** WiFi SSID */
#define CONFIG_PASSWORD "casa2020" /** WiFi Password */

// #define CONFIG_SSID "" /** WiFi SSID */
// #define CONFIG_PASSWORD "" /** WiFi Password */

#define CONFIG_MQTT_SERVER "broker.mqtt-dashboard.com" /** MQTT Server */
#define CONFIG_MQTT_TOPIC "a03monitoring" /** MQTT Topic */
#define CONIFG_MQTT_QOS 1 /** MQTT QoS */
#define CONFIG_MQTT_PORT 1883 /** MQTT Port */
#define CONFIG_CLIENT_ID "a03" /** MQTT Client ID */

#define CONFIG_RECONNECTION_INTERVAL 5000 /** Reconnection interval (milliseconds) */
#define CONFIG_BAUD_RATE 115200 /** Baud rate */

#define CONFIG_LED_OK_PIN 16 /** LED OK Pin */
#define CONFIG_LED_ERROR_PIN 17 /** LED Error Pin */
#define CONFIG_THERMISTOR_PIN 18 /** Thermistor Pin */

#define CONFIG_TASK_DEPTH 10000 /** Task Depth */