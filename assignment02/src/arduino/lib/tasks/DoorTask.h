#ifndef __DOOR_TASK__
#define __DOOR_TASK__

#include "Task.h"
#include "../components/logical/Door.h"
#include "../components/physical/Button.h"
#include "../Constants.h"

class DoorTask : public Task {   
public:
  DoorTask(Door& door, Button& closeButton, Button& openButton);
  void init(int period);
  void tick();

private:
  enum State { CLOSED, OPENED, OPERATOR_OPENED };
  State _state;
  Door* _door;
  Button* _closeButton;
  Button* _openButton;

  String MSG_PRESS_CLOSE = "Press Close When Done";
  String MSG_WASTE_RECEIVED = "Waste Received";
};

#endif