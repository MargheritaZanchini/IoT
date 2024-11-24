#include "../lib/Scheduler.h"

#include "../lib/components/Button.h"
#include "../lib/components/LCD.h"
#include "../lib/components/Led.h"
#include "../lib/components/Pir.h"
#include "../lib/components/ServoMotor.h"
#include "../lib/components/Sonar.h"


#include "../lib/tasks/UserDetectorTask.h"
#include "../lib/tasks/WasteDetectorTask.h"
#include "../lib/tasks/DoorTask.h"
#include "../lib/tasks/UserScreenTask.h"
#include "../lib/tasks/LedsTask.h"
#include "../lib/tasks/TemperatureTask.h"

#include "Arduino.h"

Scheduler sched;

void setup() {
    Serial.begin(9600);
    sched.init(50);
 
    PIR pir(13);

    Task* t0 = new UserDetectorTask(pir);
    t0->init(150);

    //Task* t1 = new WasteDetectorTask(12);
    //t1->init(500);

    ServoMotor servo(2);

    Task* t2 = new DoorTask(servo);
    t2->init(500);

    LCD lcd(0x27);

    Task* t3 = new UserScreenTask(lcd);
    t3->init(500);

    Led l1(8);
    Led l2(9);

    Task* t4 = new LedsTask(l1, l2);
    t4->init(500);

    //Task* t5 = new TemperatureTask();
    //t5->init(500);
  
    sched.addTask(t0);
    //sched.addTask(t1);
    sched.addTask(t2);
    sched.addTask(t3);
    sched.addTask(t4);
    //sched.addTask(t5);
}

void loop() {
    sched.schedule();
}

