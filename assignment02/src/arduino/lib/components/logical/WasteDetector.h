#pragma once

#include "../physical/Sonar.h"

/**
 * @brief Waste Detector Logical Component
 * @implements{Sonar}
 * @authors Marco Marrelli, Margherita Zanchini, Sofia Caberletti
 */
class WasteDetector : public Sonar {
public:
    /**
     * @brief Creates new Waste Detector
     * @param trig Output pin for Trigger Signal
     * @param echo Input pin for Sonar Echo Signal
     */
    WasteDetector(int trig, int echo) : Sonar(trig, echo) { }
    
    /**
     * @brief Map Value to Range
     * @param value Value to Map
     * @return Mapped Value (0.00 - 1.00) Representing Fill Level
     */
    float mapValue(float value = -1) {
        if (value == -1) value = read();
        
        if(value >= Constants::Sonar::EMPTY_DISTANCE) return 0.0;
        if(value <= Constants::Sonar::FULL_DISTANCE) return 1.0;
        return ((Constants::Sonar::EMPTY_DISTANCE-value) / (Constants::Sonar::EMPTY_DISTANCE-Constants::Sonar::FULL_DISTANCE));
    }

    /**
     * @brief Get Waste Level as Percentage (%)
     * @return Mapped Value (0.0% - 100.0%) Representing Fill Level
     */
    float formatLevel() {
        return mapValue(read())*100.0;
    }
};
