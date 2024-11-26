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

#include "Arduino.h"

#include "../lib/Constants.h"
//#include "EnableInterrupt.h"

Scheduler sched;

void setup() {
    Serial.begin(9600);
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

    Task* t0 = new UserDetectorTask(pir);
    t0->init(150);

    Task* t1 = new WasteDetectorTask(sonar);
    t1->init(500);

    Task* t2 = new DoorTask(servoMotor, closeButton, openButton);
    t2->init(500);

    Task* t3 = new UserScreenTask(lcd);
    t3->init(500);

    Task* t4 = new LedsTask(greenLed, redLed);
    t4->init(500);

    Task* t5 = new TemperatureTask(thermistor);
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
