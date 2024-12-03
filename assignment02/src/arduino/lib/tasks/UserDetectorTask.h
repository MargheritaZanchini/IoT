#pragma once

#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/components/physical/Pir.h"

class UserDetectorTask : public Task {
public:
    void tick() override;
    UserDetectorTask(PIR* pir);

private:
    bool _sleep;
    bool _userDetected;
    unsigned long _lastDetectedTime;
    enum State {NOT_DETECTED, DETECTED, SLEEP};
    State _state;
    PIR* _pir;
};
