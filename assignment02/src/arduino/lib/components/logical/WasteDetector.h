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
    WasteDetector(int trig, int echo) : Sonar(trig, echo) {
        // _value = read();
    }
    
    /**
     * @brief Map Value to Range
     * @param value Value to Map
     * @return Mapped Value (0.00 - 1.00) Representing Fill Level
     */
    float mapValue(float value) {
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

    /**
     * @brief Check if Container is Full
     * @return if Waste Level >= Alarm Threshold @see{Constants::Sonar::ALARM_THRESHOLD}
     */
    bool isFull() {
        return (read() >= Constants::Sonar::ALARM_THRESHOLD);
    }

// private:
//     float _value;
};
