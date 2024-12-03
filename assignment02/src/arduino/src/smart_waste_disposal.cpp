/**
 * Smart Waste Disposal
 * 
 * \brief Assignment02 - ESIoT 2024-2025 @ Unibo (Cesena)
 * \authors Marco Marrelli, Margherita Zanchini, Sofia Caberletti
 * \date 03/12/2024
 * \version 1.0
**/
#include <Arduino.h>
#include <EnableInterrupt.h>

#include "arduino/lib/Constants.h"
#include "arduino/lib/Scheduler.h"

#include "arduino/lib/components/physical/Button.h"
#include "arduino/lib/components/physical/Led.h"
#include "arduino/lib/components/physical/Pir.h"
#include "arduino/lib/components/logical/Door.h"
#include "arduino/lib/components/logical/WasteDetector.h"
#include "arduino/lib/components/logical/TemperatureDetector.h"

#include "arduino/lib/tasks/UserDetectorTask.h"
#include "arduino/lib/tasks/UserDisplayTask.h"
#include "arduino/lib/tasks/WasteDetectorTask.h"
#include "arduino/lib/tasks/DoorTask.h"
#include "arduino/lib/tasks/LedsTask.h"
#include "arduino/lib/tasks/TemperatureTask.h"

Scheduler scheduler; /** Schedule Object for Managing Tasks */

Sonar* sonar; /** [Pointer] Sonar Sensor */
Thermistor* thermistor; /** [Pointer] Thermistor Sensor */
ServoMotor* servo; /** [Pointer] Servo Motor */

Button* closeButton; /** [Pointer] Close Button */
Button* openButton; /** [Pointer] Open Button */
Led* okLED; /** [Pointer] OK Indicator LED */
Led* errorLED; /** [Pointer] Error Indicator LED */
PIR* pir; /** [Pointer] PIR Sensor */
WasteDetector* wasteDetector; /** [Pointer] Waste Detector (Sonar Handler Class) */
TemperatureDetector* temperatureDetector; /** [Pointer] Temperature Detector (Thermistor Handler Class) */
Door* door; /** [Pointer] Door (ServoMotor Handler Class) */

DoorTask* doorManager; /** [Pointer] Door Task */
UserDetectorTask* userDetecion; /** [Pointer] User Detection Task */
TemperatureTask* temperatureDetection; /** [Pointer] Temperature Detection Task */
WasteDetectorTask* wasteDetection; /** [Pointer] Waste Detection Task */
LedsTask* ledManager; /** [Pointer] LEDs Management Task */
UserDisplayTask* userDisplay; /** [Pointer] User Display Task */

/**
 * \brief Wakeup Function for Sleep State
 */
void wakeup() { }

/**
 * \brief Setup Function
 */
void setup() {
    Serial.begin(Constants::BAUD_RATE);
    Serial.flush();

    enableInterrupt(Constants::PIR::PIN, wakeup, RISING);

    closeButton = new Button(Constants::Button::Close::PIN);
    openButton = new Button(Constants::Button::Open::PIN);
    okLED = new Led(Constants::LED::OK::PIN);
    errorLED = new Led(Constants::LED::Error::PIN);
    pir = new PIR(Constants::PIR::PIN);
    sonar = new Sonar(Constants::Sonar::Trigger::PIN, Constants::Sonar::Echo::PIN);
    thermistor = new Thermistor(Constants::Thermistor::PIN);
    servo = new ServoMotor(Constants::Servo::PIN);

    door = new Door(servo);
    wasteDetector = new WasteDetector(sonar);
    temperatureDetector = new TemperatureDetector(thermistor);

    doorManager = new DoorTask(door, closeButton, openButton, temperatureDetector, wasteDetector);
    doorManager->init(500);

    userDetecion = new UserDetectorTask(pir);
    userDetecion->init(500);

    temperatureDetection = new TemperatureTask(temperatureDetector);
    temperatureDetection->init(500);

    wasteDetection = new WasteDetectorTask(wasteDetector);
    wasteDetection->init(500);

    ledManager = new LedsTask(okLED, errorLED, temperatureDetector, wasteDetector);
    ledManager->init(500);

    userDisplay = new UserDisplayTask(wasteDetector, temperatureDetector, door);
    userDisplay->init(1000);

    scheduler.init(500);

    scheduler.addTask(doorManager);
    scheduler.addTask(userDetecion);
    scheduler.addTask(temperatureDetection);
    scheduler.addTask(wasteDetection);
    scheduler.addTask(ledManager);
    scheduler.addTask(userDisplay);
}

/**
 * \brief Main Loop
 */
void loop() {
    scheduler.schedule();
}
