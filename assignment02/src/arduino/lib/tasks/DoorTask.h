#ifndef __A02_DOOR_TASK__
#define __A02_DOOR_TASK__

#include "Task.h"
#include "../components/logical/Door.h"
#include "../components/physical/Button.h"
#include "../Constants.h"
#include "../components/logical/TemperatureDetector.h"
#include "../components/logical/WasteDetector.h"
#include "../../lib/communication/MsgService.h"

class DoorTask : public Task {   
public:
  DoorTask(Door& door, Button& closeButton, Button& openButton, TemperatureDetector& temperatureDetector, WasteDetector& wasteDetector);
  void init(int period);
  void tick();

private:
  enum State { CLOSED, OPENED, OPERATOR_OPENED };
  State _state;
  Door* _door;
  Button* _closeButton;
  Button* _openButton;
  WasteDetector* _wasteDetector;
  TemperatureDetector* _temperatureDetector;
  unsigned long _lastEmptiedTime;
};

#endif