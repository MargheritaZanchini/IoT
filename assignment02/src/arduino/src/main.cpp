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
//#include "EnableInterrupt.h"

#define SERVO_PIN 2
#define PIR_PIN 5
#define CLOSE_BUTTON_PIN 6
#define OPEN_BUTTON_PIN 7
#define OK_LED_PIN 8
#define ERROR_LED_PIN 9
#define SONAR_TRIG_PIN 12
#define SONAR_ECHO_PIN 13
#define THERMO_PIN A0
#define LCD_ADDRESS 0x27
#

Scheduler sched;

void setup() {
    Serial.begin(9600);
    sched.init(50);
 
    Button closeButton(CLOSE_BUTTON_PIN);
    Button openButton(OPEN_BUTTON_PIN);
    LCD lcd(LCD_ADDRESS);
    Led greenLed(OK_LED_PIN);
    Led redLed(ERROR_LED_PIN);
    PIR pir(PIR_PIN);
    ServoMotor servoMotor(SERVO_PIN);
    Sonar sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
    Thermistor thermistor(THERMO_PIN);

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
