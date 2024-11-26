#ifndef __DOOR_TASK__
#define __DOOR_TASK__

#include "Task.h"

#include "../components/ServoMotor.h"
#include "../components/Button.h"

#define MSG_PRESS_CLOSE "Press Close When Done"
#define MSG_WASTE_RECEIVED "Waste Received"
#define DELTA_T2 3000

#define USER_DOOR_OPENED 90
#define OPERATOR_DOOR_OPENED -90
#define USER_DOOR_CLOSED 0

class DoorTask : public Task {   
public:
  DoorTask(ServoMotor& servo, Button& closeButton, Button& openButton, bool& full, bool& alarm, String msg, long& time);
  void init(int period);
  void tick();

private:
  enum State { CLOSED, OPENED, OPERATOR_OPENED };
  State _state;
  ServoMotor* _servo;
  Button* _closeButton;
  Button* _openButton;
  bool* _full;
  bool* _alarm;
  String _msg;
  long* _time;
};

#endif