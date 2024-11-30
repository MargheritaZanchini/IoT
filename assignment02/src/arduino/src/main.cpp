#include "../lib/Scheduler.h"
#include "../lib/components/physical/Button.h"
#include "../lib/components/physical/Led.h"
#include "../lib/components/physical/Pir.h"
#include "../lib/components/logical/Display.h"
#include "../lib/components/logical/Door.h"
#include "../lib/components/logical/WasteDetector.h"
#include "../lib/components/logical/TemperatureDetector.h"

#include "../lib/tasks/UserDetectorTask.h"
#include "../lib/tasks/UserDisplayTask.h"
#include "../lib/tasks/WasteDetectorTask.h"
#include "../lib/tasks/DoorTask.h"
#include "../lib/tasks/LedsTask.h"
#include "../lib/tasks/TemperatureTask.h"

#include <Arduino.h>
#include "EnableInterrupt.h"

#include "../lib/Constants.h"
#include "../lib/communication/MsgService.h"

Scheduler scheduler;

void wakeUp(){ }

void setup() {
    Serial.begin(Constants::BAUD_RATE);
    scheduler.init(250);

    Button closeButton(Constants::Button::Close::PIN);
    Button openButton(Constants::Button::Open::PIN);
    //Display display(Constants::LCD::ADDRESS);
    Led okIndicator(Constants::LED::OK::PIN);
    Led errorIndicator(Constants::LED::Error::PIN);
    PIR pir(Constants::PIR::PIN);
    Door door(Constants::Servo::PIN);
    WasteDetector wasteDetector(Constants::Sonar::Trigger::PIN, Constants::Sonar::Echo::PIN);
    TemperatureDetector temperatureDetector(Constants::Thermistor::PIN);

    enableInterrupt(Constants::PIR::PIN, wakeUp, RISING);

    Task* doorManager = new DoorTask(door, closeButton, openButton, temperatureDetector, wasteDetector);
    doorManager->init(500);

    Task* userDetecion = new UserDetectorTask(pir);
    userDetecion->init(500);

    Task* temperatureDetection = new TemperatureTask(temperatureDetector);
    temperatureDetection->init(500);
 
    Task* wasteDetection = new WasteDetectorTask(wasteDetector);
    wasteDetection->init(500);

    Task* ledManager = new LedsTask(okIndicator, errorIndicator, temperatureDetector);
    ledManager->init(500);

    //Task* userDisplay = new UserDisplayTask(display, wasteDetector, temperatureDetector, door);
    //userDisplay->init(1000);

    scheduler.addTask(doorManager);
    scheduler.addTask(userDetecion);
    scheduler.addTask(temperatureDetection);
    scheduler.addTask(wasteDetection);
    scheduler.addTask(ledManager);
    //scheduler.addTask(userDisplay);
}

void loop() {
    scheduler.schedule();
}