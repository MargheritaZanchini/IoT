/**
 * Smart Waste Disposal
 * 
 * \brief Assignment02 - ESIoT 2024-2025 @ Unibo (Cesena)
 * \authors Marco Marrelli, Margherita Zanchini, Sofia Caberletti
 * \date 03/12/2024
 * \version 1.0
**/
#include <Arduino.h>

#include "../lib/components/physical/Button.h"
#include "../lib/components/logical/Window.h"

#include "../lib/tasks/WindowTask.h"
#include "../lib/tasks/DisplayTask.h"

#include "../lib/tasks/Scheduler.h"

Scheduler scheduler; /** Schedule Object for Managing Tasks */

ServoMotor* servo; /** [Pointer] Servo Motor */

Button* modeButton; /** [Pointer] Close Button */
Window* window; /** [Pointer] Window (ServoMotor Handler Class) */

WindowTask* windowManager; /** [Pointer] Window Task */
DisplayTask* displayManager; /** [Pointer] User Display Task */

/**
 * \brief Wakeup Function for Sleep State
 */
void wakeup() { }

/**
 * \brief Setup Function
 */
void setup() {
    Serial.begin(CONFIG_SERIAL_BAUD_RATE);
    Serial.flush();

    servo = new ServoMotor(CONFIG_SERVO_PIN);

    window = new Window(servo);

    windowManager = new WindowTask(window);
    windowManager->init(500);

    displayManager = new DisplayTask(window);
    displayManager->init(1000);

    scheduler.init(500);

    scheduler.addTask(windowManager);
    scheduler.addTask(displayManager);
}

/**
 * \brief Main Loop
 */
void loop() {
    scheduler.schedule();
}
