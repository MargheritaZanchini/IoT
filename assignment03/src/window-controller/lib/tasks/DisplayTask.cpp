#include "DisplayTask.h"

#include <Arduino.h>

DisplayTask::DisplayTask(Window* window) {
    _lcd.init();
    _lcd.backlight();
    _lcd.setCursor(0, 0);

    _window = window;

    updateDisplay("");
}

/**
 * \brief Initializes the Task
 * 
 * Message Format:
 * - current opening of the window
 * - current mode (AUTOMATIC / MANUAL)
 * - current temperature value (MANUAL)
 */
void DisplayTask::tick() {

}

void DisplayTask::updateDisplay(const char* msg) {
    if(_previousMessage == msg) {
        return;
    }

    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print(msg);
    _previousMessage = msg;
}