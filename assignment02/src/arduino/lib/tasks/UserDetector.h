#ifndef __USERDETECTOR__
#define __USERDETECTOR__

#include "Task.h"
#include "components/Pir.h"

class UserDetector : public Task{

public:
    void init(int period);
    void tick();
    UserDetector(/* args */);

private:
    bool _sleep;
    int _deltaTime;
    int _userDetected;
    long _lastDetectedTime;
    enum State {NOT_DETECTED, DETECTED, SLEEP};
    State _state;
    Pir _pir;
};


#endif