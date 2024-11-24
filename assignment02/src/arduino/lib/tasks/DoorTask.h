#ifndef __DOOR_TASK__
#define __DOOR_TASK__

#include "Task.h"
#include "../components/ServoMotor.h"

#define USER_DOOR_OPENED 90
#define OPERATOR_DOOR_OPENED -90
#define USER_DOOR_CLOSED 0

class DoorTask : public Task {   
public:
  DoorTask(ServoMotor& servo);
  void init(int period);
  void tick();

private:
  enum State { CLOSED, OPENED, OPERATOR_OPENED };
  State _state;
  ServoMotor* _servo;
};

#endif