#ifndef __LEDS_TASK__
#define __LEDS_TASK__

#include "Task.h"

class LedsTask: public Task {
public:
    LedsTask(int pin1, int pin2);  
    void init(int period);  
    void tick();

private:
    int _pin1, _pin2;
    enum State { L1_ON, L2_ON};
    State _state;
};

#endif