#pragma once

#include "Task.h"
#include "../components/physical/Led.h"

class LedsTask: public Task {
public:
    LedsTask(Led& ok, Led& error);  
    void init(int period);
    void tick();

private:
    Led* _ok;
    Led* _error;

    enum State { OK_ON, ERROR_ON};
    State _state;
};