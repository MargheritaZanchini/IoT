#pragma once

#include <Arduino.h>
#include "arduino/lib/components/physical/Sonar.h"

/**
 * @brief Waste Detector Logical Component
 */
class WasteDetector {
public:
    /**
     * @brief Creates new Waste Detector
     * @param sonar Reference to a Sonar Object
     */
    WasteDetector(Sonar* sonar);

    /**
     * @brief Map Value to Range
     * @param value Value to Map
     * @return Mapped Value (0.00 - 1.00) Representing Fill Level
     */
    float mapValue(float value = -1);

    /**
     * @brief Get Waste Level as Percentage (%)
     * @return Mapped Value (0.0% - 100.0%) Representing Fill Level
     */
    float getFormattedValue();

    /**
     * @brief Check if Container is Full
     * @return if Waste Level >= Alarm Threshold @see{Constants::Sonar::ALARM_THRESHOLD}
     */
    bool getFullnessAlarm();

    /**
     * @brief Set Container Fullness
     * @param isFull if Container is Full
     */
    void setFullnessAlarm(bool isFull);

    /**
     * @brief Read Waste Level
     * @return Waste Level in Meters
     */
    float read();

private:
    Sonar* _sonar; /** Reference to the Sonar Object */
    bool _isFullAlarm = false; /** Fullness Alarm Status */
};