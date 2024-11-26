#include "../lib/Scheduler.h"
#include "../lib/components/Button.h"
#include "../lib/components/LCD.h"
#include "../lib/components/Led.h"
#include "../lib/components/Pir.h"
#include "../lib/components/ServoMotor.h"
#include "../lib/components/Sonar.h"
#include "../lib/components/Thermistor.h"

#include "../lib/tasks/UserDetectorTask.h"
#include "../lib/tasks/WasteDetectorTask.h"
#include "../lib/tasks/DoorTask.h"
#include "../lib/tasks/UserScreenTask.h"
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
    sched.init(50);
 
    Button closeButton(Constants::Button::Close::PIN);
    Button openButton(Constants::Button::Open::PIN);
    LCD lcd(Constants::LCD::ADDRESS);
    Led greenLed(Constants::LED::OK::PIN);
    Led redLed(Constants::LED::Error::PIN);
    PIR pir(Constants::PIR::PIN);
    ServoMotor servoMotor(Constants::Servo::PIN);
    Sonar sonar(Constants::Sonar::Trigger::PIN, Constants::Sonar::Echo::PIN);
    Thermistor thermistor(Constants::Thermistor::PIN);

    //tempo per calibrare il PIR
    Serial.println("Calibrating...");
    delay(Constants::PIR::CALIBRATION_TIME);

    Serial.println("prima di attaccare l'interrupt");

    enableInterrupt(Constants::PIR::PIN, wakeUp, RISING); // Link the Interrupt to the wakeUp() Function

    Serial.println("Interrupt attaccato");

    UserDetectorTask* t0 = new UserDetectorTask(pir);
    t0->init(150);

    UserScreenTask* t1 = new UserScreenTask(lcd);
    t1->init(500);

    WasteDetectorTask* t2 = new WasteDetectorTask(sonar, t1->msg, t1->clear);
    t2->init(500);

    TemperatureTask* t3 = new TemperatureTask(thermistor, t1->msg, t1->clear);
    t3->init(500);

    // DoorTask* t4 = new DoorTask(servoMotor, closeButton, openButton, ((WasteDetectorTask*) t2)->full, ((TemperatureTask*) t3)->alarm);
    DoorTask* t4 = new DoorTask(servoMotor, closeButton, openButton, t2->full, t3->alarm, t1->msg, t1->time);
    t4->init(500);

    LedsTask* t5 = new LedsTask(greenLed, redLed, t2->full, t3->alarm);
    t5->init(500);

    sched.addTask(t0);
    sched.addTask(t1);
    sched.addTask(t2);
    sched.addTask(t3);
    sched.addTask(t4);
    sched.addTask(t5);
}

void loop() {
    sched.schedule();
}
