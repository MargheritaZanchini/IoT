#include "../lib/Scheduler.h"
#include "../lib/components/physical/Button.h"
#include "../lib/components/physical/Led.h"
#include "../lib/components/physical/Pir.h"
// #include "../lib/components/logical/Door.h"
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

// Scheduler scheduler;

Button* closeButton; // = new Button(Constants::Button::Close::PIN);
Button* openButton; // = new Button(Constants::Button::Open::PIN);
Led* okIndicator; // = new Led(Constants::LED::OK::PIN);
Led* errorIndicator; // = new Led(Constants::LED::Error::PIN);
PIR* pir; // = new PIR(Constants::PIR::PIN);
ServoMotor* door; // = new Door(Constants::Servo::PIN);
WasteDetector* wasteDetector; // = new WasteDetector(Constants::Sonar::Trigger::PIN, Constants::Sonar::Echo::PIN);
TemperatureDetector* temperatureDetector; // = new TemperatureDetector(Constants::Thermistor::PIN);

void wakeUp() { }

void setup() {
    // closeButton = new Button(Constants::Button::Close::PIN);
    // openButton = new Button(Constants::Button::Open::PIN);
    // okIndicator = new Led(Constants::LED::OK::PIN);
    // errorIndicator = new Led(Constants::LED::Error::PIN);
    // pir = new PIR(Constants::PIR::PIN);
    door = new ServoMotor(Constants::Servo::PIN);
    // wasteDetector = new WasteDetector(Constants::Sonar::Trigger::PIN, Constants::Sonar::Echo::PIN);
    // temperatureDetector = new TemperatureDetector(Constants::Thermistor::PIN);

    Serial.begin(Constants::BAUD_RATE);
    Serial.flush();

    // scheduler.init(500);

    // enableInterrupt(Constants::PIR::PIN, wakeUp, RISING);

    // DoorTask* doorManager = new DoorTask(door, closeButton, openButton, temperatureDetector, wasteDetector);
    // doorManager->init(500);

    // UserDetectorTask* userDetecion = new UserDetectorTask(pir);
    // userDetecion->init(500);

    // TemperatureTask* temperatureDetection = new TemperatureTask(temperatureDetector);
    // temperatureDetection->init(500);

    // WasteDetectorTask* wasteDetection = new WasteDetectorTask(wasteDetector);
    // wasteDetection->init(500);

    // LedsTask* ledManager = new LedsTask(okIndicator, errorIndicator, temperatureDetector, wasteDetector);
    // ledManager->init(500);

    // UserDisplayTask* userDisplay = new UserDisplayTask(wasteDetector, temperatureDetector);
    // userDisplay->init(1000);

    // scheduler.addTask(doorManager);
    // scheduler.addTask(userDetecion);
    // scheduler.addTask(temperatureDetection);
    // scheduler.addTask(wasteDetection);
    // scheduler.addTask(ledManager);
    // scheduler.addTask(userDisplay);
}

void loop() {
    // scheduler.schedule();
    door->setPosition(750);
    delay(1000);
    door->setPosition(1500);
    delay(1000);
}

/** 
#include <Arduino.h>
#include "../lib/components/physical/ServoMotor.h"

ServoMotor* servo;

void setup() {
    Serial.begin(9600);
    Serial.println("Inizio Setup");

    servo = new ServoMotor(2);
    servo->on();
    Serial.println("Fine Setup");
}

void loop() {
    servo->setPosition(1500);
    delay(1000);
    servo->setPosition(750);
    delay(1000);
}
*/