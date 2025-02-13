#include <Arduino.h>

#include "Communication.h"
#include "Monitoring.h"

#include "config.h"



WiFiClient* wifiClient; /** WiFi Client */
PubSubClient* pubSubClient; /** MQTT Client */

Communication* communication;
Monitoring* monitoring;

TaskHandle_t taskHandle; /** Task Handle */

int frequency = 5000; /** Frequency (Normal = F1, Hot = F2) */



/**
 * \brief Check if a string is convertible to an integer
 * 
 * \param value String to check
 * \return bool
 */
bool isInteger(String value);

/**
 * \brief Task to read the new frequency sent from the Control Unit.
 * 
 * \param topic MQTT Topic of the message
 * \param payload Message arrived
 * \param length Length of the message
 */
void callback(char* topic, byte* payload, unsigned int length);

/**
 * \brief Monitoring Task Code
 * 
 * \param argument Task Arguments
 */
void monitoringTaskCode(void *argument);



bool isInteger(String value) {
    if(value.isEmpty()) return false; // If Empty String, return False

    // Iterate over every char, if not a digit return false
    for(int i=0; i<value.length(); i++) {
        if(!isDigit(value.charAt(i))) {
            return false;
        }
    }

    // If all characters are digits return true
    return true;
}

void callback(char* topic, byte* payload, unsigned int length) {
    // Convert the payload to a string and store it in a variable
    String message = "";
    for(int i=0; i<length; i++) {
        message += (char) payload[i];
    }

    // Print the message and its topic to Serial
    Serial.print("Message arrived in ");
    Serial.print(topic);
    Serial.print(": ");
    Serial.println(message);

    // Check if the message is a frequency message
    if(message.startsWith("frequency:")) {
        String value = message.substring(10); // Extract the value from the message
        
        // If the value is convertible to an integer,
        // Convert it and store it in the frequency variable
        if(isInteger(value)) {
            //frequency = value.toInt();
            
            // Print the new frequency to Serial
            //Serial.print("Frequency Changed to: ");
            //Serial.println(frequency);

            int newFrequency = value.toInt();
            if (newFrequency > 0) {
                frequency = newFrequency;
                // Print the new frequency to Serial
                Serial.print("Frequency Changed to: ");
                Serial.println(frequency);
            } else {
                Serial.println("Invalid Frequency Value Received: Must be greater than 0");
            }
        }
        else { // Else, if not convertible, print an error message and exit the function
            Serial.println("Invalid Frequency Value Received");
            return;
        }
    }
}

void monitoringTaskCode(void *argument) {
    TickType_t _lastWakeTime, _frequency;

    for(;;) {
        //_frequency = pdMS_TO_TICKS(frequency);
        //monitoring->eventLoop();
        //vTaskDelayUntil(&_lastWakeTime, _frequency);

        _frequency = pdMS_TO_TICKS(frequency);
        if (_frequency > 0) {
            monitoring->eventLoop();
            vTaskDelayUntil(&_lastWakeTime, _frequency);
        } else {
            Serial.println("Frequency is zero, skipping delay");
            vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second to avoid busy loop
        }
    }
}



/**
 * \brief Setup Function
 */
void setup() {
    Serial.begin(CONFIG_BAUD_RATE); // Start Serial Communication with the specified baud rate

    // Initialize the WiFi and MQTT Clients
    wifiClient = new WiFiClient();
    pubSubClient = new PubSubClient(*wifiClient);
    communication = new Communication(wifiClient, pubSubClient);

    // Begin the Communication
    communication->begin();

    // Set the Callback Function for the MQTT Client
    communication->setCallback(callback);

    // Initialize the Monitoring Task Class
    monitoring = new Monitoring();
    xTaskCreatePinnedToCore(monitoringTaskCode, "Monitoring Task", CONFIG_TASK_DEPTH, NULL, 1, &taskHandle, 1);
}

/**
 * \brief Loop Function
 */
void loop() {
    communication->eventLoop();
}
