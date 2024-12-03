#pragma once

#include "arduino/lib/Constants.h"
#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/communication/SerialHandler.h"
#include "arduino/lib/components/physical/Button.h"
#include "arduino/lib/components/logical/Door.h"
#include "arduino/lib/components/logical/TemperatureDetector.h"
#include "arduino/lib/components/logical/WasteDetector.h"

class DoorTask : public Task {   
public:
    DoorTask(Door* door, Button* closeButton, Button* openButton, TemperatureDetector* temperatureDetector, WasteDetector* wasteDetector);
    void tick() override;

private:
    enum State { CLOSED, OPENED, OPERATOR_OPENED };
    State _state;
    Door* _door;
    Button* _closeButton;
    Button* _openButton;
    WasteDetector* _wasteDetector;
    TemperatureDetector* _temperatureDetector;
    unsigned long _lastEmptiedTime;
    unsigned long _automaticCloseTime;
};
