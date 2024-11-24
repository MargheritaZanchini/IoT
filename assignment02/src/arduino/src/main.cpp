#include "../lib/Scheduler.h"
#include "../lib/tasks/UserDetectorTask.h"
#include "../lib/tasks/WasteDetectorTask.h"
#include "../lib/tasks/DoorTask.h"
#include "../lib/tasks/UserScreenTask.h"
#include "../lib/tasks/LedsTask.h"
#include "../lib/tasks/TemperatureTask.h"

#include <Arduino.h>

Scheduler sched;

void setup() {
    Serial.begin(9600);
    sched.init(50);
 
    PIR pir(13);

    Task* t0 = new UserDetectorTask(pir);
    t0->init(150);

    /*Task* t1 = new WasteDetectorTask(12);
    t1->init(500);

    Task* t2 = new DoorTask(2);
    t2->init(500);

    Task* t3 = new UserScreenTask();
    t3->init(500);

    Task* t4 = new LedsTask();
    t4->init(500);

    Task* t5 = new TemperatureTask();
    t5->init(500);*/
  
    sched.addTask(t0);
    /*sched.addTask(t1);
    sched.addTask(t2);
    sched.addTask(t3);
    sched.addTask(t4);
    sched.addTask(t5);*/
}

void loop() {
    sched.schedule();
}

