#ifndef __A02_USER_DETECTOR_TASK__
#define __A02_USER_DETECTOR_TASK__

#include "Task.h"
#include "../components/physical/Pir.h"

class UserDetectorTask : public Task{

public:
    // void init(int period);
    void tick() override;
    UserDetectorTask(PIR* pir);
private:
    bool _sleep;
    bool _userDetected;
    unsigned long _deltaTime;
    unsigned long _lastDetectedTime;
    enum State {NOT_DETECTED, DETECTED, SLEEP};
    State _state;
    PIR* _pir;
};

#endif