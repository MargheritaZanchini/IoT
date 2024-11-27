#include "../lib/Scheduler.h"
#include "../lib/components/physical/Button.h"
#include "../lib/components/physical/Led.h"
#include "../lib/components/physical/Pir.h"
#include "../lib/components/logical/Display.h"
#include "../lib/components/logical/Door.h"
#include "../lib/components/logical/WasteDetector.h"
#include "../lib/components/logical/TemperatureDetector.h"

#include "../lib/tasks/UserDetectorTask.h"
#include "../lib/tasks/WasteDetectorTask.h"
#include "../lib/tasks/DoorTask.h"
#include "../lib/tasks/LedsTask.h"
#include "../lib/tasks/TemperatureTask.h"

#include <Arduino.h>
#include "EnableInterrupt.h"

#include "../lib/Constants.h"

Scheduler sched;

void wakeUp(){

}

void setup() {
    Serial.begin(Constants::BAUD_RATE);
    sched.init(100);
 
    Button closeButton(Constants::Button::Close::PIN);
    Button openButton(Constants::Button::Open::PIN);
    LCD lcd(Constants::LCD::ADDRESS);
    Led greenLed(Constants::LED::OK::PIN);
    Led redLed(Constants::LED::Error::PIN);
    PIR pir(Constants::PIR::PIN);
    Door door(Constants::Servo::PIN);
    WasteDetector wasteDetector(Constants::Sonar::Trigger::PIN, Constants::Sonar::Echo::PIN);
    TemperatureDetector temperatureDetector(Constants::Thermistor::PIN);

    //tempo per calibrare il PIR
    Serial.println("Calibrating...");
    delay(Constants::PIR::CALIBRATION_TIME);

    Serial.println("prima di attaccare l'interrupt");

    enableInterrupt(Constants::PIR::PIN, wakeUp, RISING); // Link the Interrupt to the wakeUp() Function

    Serial.println("Interrupt attaccato");

    // OK
    Task* t0 = new UserDetectorTask(pir);
    t0->init(400);
 
    /*
        Task* t1 = new UserDisplayTask(lcd, wasteDetector, temperatureDetector, door);
    */

    // NEEDS LCD
    Task* t2 = new WasteDetectorTask(wasteDetector, lcd);
    t2->init(500);

    // NEEDS LCD
    Task* t3 = new TemperatureTask(temperatureDetector);
    t3->init(500);

    // NEEDS LCD
    Task* t4 = new DoorTask(door, closeButton, openButton);
    t4->init(100);

    Task* t5 = new LedsTask(greenLed, redLed);
    t5->init(100);

    
    sched.addTask(t0);
    sched.addTask(t2);
    sched.addTask(t3);
    sched.addTask(t4);
    sched.addTask(t5);
}

void loop() {
    sched.schedule();
}
