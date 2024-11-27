#ifndef __LEDS_TASK__
#define __LEDS_TASK__

#include "Task.h"
#include "../components/physical/Led.h"

class LedsTask: public Task {
public:
    LedsTask(Led& L1, Led& L2, bool& full, bool& alarm);  
    void init(int period);  
    void tick();

private:
    enum State { L1_ON, L2_ON};
    State _state;
    Led* _L1;
    Led* _L2;
    bool* _full;
    bool* _alarm;
};

#endif