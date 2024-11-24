#ifndef __USER_SCREEN_TASK__
#define __USER_SCREEN_TASK__

#include "Task.h"
#include "../components/LCD.h"

class UserScreenTask: public Task {
public:
    UserScreenTask(LCD& lcd);  
    void init(int period);  
    void tick();

private:
    int _pin;
    enum State { PRINT_DEFAULT, PRINT};
    State _state;
    LCD* _lcd;
};

#endif