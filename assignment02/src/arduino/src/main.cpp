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

Scheduler scheduler;

void wakeUp(){ }

void setup() {
    Serial.begin(Constants::BAUD_RATE);
    scheduler.init(100);

    Button closeButton(Constants::Button::Close::PIN);
    Button openButton(Constants::Button::Open::PIN);
    Display display(Constants::LCD::ADDRESS);
    Led okIndicator(Constants::LED::OK::PIN);
    Led errorIndicator(Constants::LED::Error::PIN);
    PIR pir(Constants::PIR::PIN);
    Door door(Constants::Servo::PIN);
    WasteDetector wasteDetector(Constants::Sonar::Trigger::PIN, Constants::Sonar::Echo::PIN);
    TemperatureDetector temperatureDetector(Constants::Thermistor::PIN);

    // Serial.println("Calibrating...");
    // delay(Constants::PIR::CALIBRATION_TIME);
    // Serial.println("prima di attaccare l'interrupt");
    // enableInterrupt(Constants::PIR::PIN, wakeUp, RISING); // Link the Interrupt to the wakeUp() Function
    // Serial.println("Interrupt attaccato");

    Task* userDetecion = new UserDetectorTask(pir);
    userDetecion->init(400);
 
    Task* wasteDetection = new WasteDetectorTask(wasteDetector);
    wasteDetection->init(500);

    Task* temperatureDetection = new TemperatureTask(temperatureDetector);
    temperatureDetection->init(500);

    Task* doorManager = new DoorTask(door, closeButton, openButton);
    doorManager->init(100);

    Task* userDisplay = new UserDisplayTask(display, wasteDetector, temperatureDetector, door);
    userDisplay->init(500);

    Task* ledManager = new LedsTask(okIndicator, errorIndicator);
    ledManager->init(100);

    scheduler.addTask(userDetecion);
    scheduler.addTask(wasteDetection);
    scheduler.addTask(temperatureDetection);
    scheduler.addTask(doorManager);
    scheduler.addTask(userDisplay);
    scheduler.addTask(ledManager);
}

void loop() {
    scheduler.schedule();
}
