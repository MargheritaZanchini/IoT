#ifndef __PIR__
#define __PIR__

#include "../physical/Pir.h"

/**
 * @brief PIR Component Helper Class
 * @implements PIR
 */
class UserDetector : public PIR {
public:
    /**
     * @brief Reads Current Motion State
     * @return true if Motion Detected, false Otherwise
     */
    const bool isUserDetected() {
        return digitalRead(_pin) == HIGH;
    }
};

#endif