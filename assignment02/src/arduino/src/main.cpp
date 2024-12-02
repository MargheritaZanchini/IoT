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
// #include "../lib/communication/MsgService.h"

Scheduler scheduler;

LiquidCrystal_I2C _lcd = LiquidCrystal_I2C(0x27, 20, 4);

// Button closeButton(Constants::Button::Close::PIN);
// Button openButton(Constants::Button::Open::PIN);
Display display(&_lcd);
// Led okIndicator(Constants::LED::OK::PIN);
// Led errorIndicator(Constants::LED::Error::PIN);
// PIR pir(Constants::PIR::PIN);
// Door door(Constants::Servo::PIN);
// WasteDetector wasteDetector(Constants::Sonar::Trigger::PIN, Constants::Sonar::Echo::PIN);
// TemperatureDetector temperatureDetector(Constants::Thermistor::PIN);

void wakeUp(){ }

void setup() {
    // MsgService.init();
    Serial.begin(Constants::BAUD_RATE);
    scheduler.init(250);

    Serial.println("Inizio setup");
    display.printDefaultMessage();
    
    // enableInterrupt(Constants::PIR::PIN, wakeUp, RISING);

    // Task* doorManager = new DoorTask(door, closeButton, openButton, temperatureDetector, wasteDetector);
    // doorManager->init(500);

    // Task* userDetecion = new UserDetectorTask(pir);
    // userDetecion->init(500);

    // Task* temperatureDetection = new TemperatureTask(&temperatureDetector);
    // temperatureDetection->init(500);
 
    // Task* wasteDetection = new WasteDetectorTask(wasteDetector);
    // wasteDetection->init(500);

    // Task* ledManager = new LedsTask(okIndicator, errorIndicator, temperatureDetector, wasteDetector);
    // ledManager->init(500);

    //Task* userDisplay = new UserDisplayTask(&display, &wasteDetector, &temperatureDetector, &door);
    Serial.println("Setup");
    Task* userDisplay = new UserDisplayTask(&display, nullptr, nullptr, nullptr);
    Serial.println("UserDisplay instanziato");
    // userDisplay->init(1000);
    Serial.println("UserDisplay inizzializzato");

    // scheduler.addTask(doorManager);
    // scheduler.addTask(userDetecion);
    // scheduler.addTask(temperatureDetection);
    // scheduler.addTask(wasteDetection);
    // scheduler.addTask(ledManager);
    // scheduler.addTask(userDisplay);
}

void loop() {
    scheduler.schedule();
}