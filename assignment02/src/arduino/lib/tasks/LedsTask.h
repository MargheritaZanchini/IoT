#ifndef __LEDS_TASK__
#define __LEDS_TASK__

#include "Task.h"
#include "../components/Led.h"

class LedsTask: public Task {
public:
    LedsTask(Led& L1, Led& L2);  
    void init(int period);  
    void tick();

private:
    Led* _L1, _L2;
    bool _alarm;
    enum State { L1_ON, L2_ON};
    State _state;
};

#endif