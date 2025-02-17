#pragma once

#include <LiquidCrystal_I2C.h>

#include "../tasks/Task.h"
#include "../communication/SerialHandler.h"
#include "../components/logical/Window.h"

/**
 * \brief User Display Task Class
 * \implements{Task}
 */
class DisplayTask : public Task {
public:
    /**
     * \brief Creates New User Display Task
     * \param window Pointer to Window Object
     */
    DisplayTask(Window* window);

    void tick() override;

private:
    LiquidCrystal_I2C _lcd = LiquidCrystal_I2C(0x27, 20, 4); /** LCD Display Object */
    Window* _window; /** Pointer to Window Object */

    const char* _previousMessage; /** Previous Message Displayed on the LCD */

    /**
     * \brief Updates the Display with a New Message, Format:
     * \brief - current opening of the window
     * \brief - current mode (AUTOMATIC / MANUAL)
     * \brief - current temperature value (MANUAL)
     * 
     * \param msg The Message to Display
     */
    void updateDisplay(const char* msg);
};