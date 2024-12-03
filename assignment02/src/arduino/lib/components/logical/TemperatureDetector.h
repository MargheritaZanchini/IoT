#pragma once

#include <Arduino.h>
#include "arduino/lib/components/physical/Thermistor.h"
#include "arduino/lib/communication/SerialHandler.h"
#include "arduino/lib/Constants.h"

/**
 * @brief Class for the Temperature Detector
 * @implements Thermistor
 */
class TemperatureDetector {
public:
    /**
     * @brief Creates New Temperature Detector Instance
     * @param thermistor Reference to a Thermistor Object
     */
    TemperatureDetector(Thermistor* thermistor);

    /**
     * @brief Read the Temperature from the Thermistor. 
     * @return Temperature in Celsius
     */
    float read();

    /**
     * @brief Check if the temperature is overheated
     * @return if the temperature is overheated
     */
    bool getTemperatureAlarm();

    /**
     * @brief Set the alarm for the temperature
     * @param alarm if the alarm is set
     */
    void setTemperatureAlarm(bool alarm);

private:
    Thermistor* _thermistor; /**< Reference to the Thermistor Object */
    bool _highTemperatureAlarm = false; /**< High Temperature Alarm Status */
};
