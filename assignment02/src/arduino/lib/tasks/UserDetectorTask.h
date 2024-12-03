#pragma once

#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/components/physical/Pir.h"

/**
 * \brief User Detector Task Class
 * \implements{Task}
 */
class UserDetectorTask : public Task {
public:
    /**
     * \brief Creates New User Detector Task
     * \param pir Pointer to PIR Sensor Object
     */
    UserDetectorTask(PIR* pir);

    void tick() override;

private:
    enum State {NOT_DETECTED, DETECTED, SLEEP}; /** Enumeration for PIR States */
    State _state; /** Current State of the User Detector Task */

    PIR* _pir; /** Pointer to PIR Sensor Object */

    bool _sleep; /** Sleep Status */
    bool _userDetected; /** User Detected Status */
    
    unsigned long _lastDetectedTime; /** Timestamp of the Last Detected User */
};
