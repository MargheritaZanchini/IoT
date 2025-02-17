#pragma once

/**
 * String used to clear the LCD Values Displayed
 */
#define DISPLAY_CLEARING_STRING "       "

#include <LiquidCrystal_I2C.h>

#include "../tasks/Task.h"
#include "../communication/SerialHandler.h"
#include "../components/logical/Window.h"
#include "../components/logical/SystemMode.h"

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
    DisplayTask(Window* window, SystemMode* mode);

    void tick() override;

private:
    LiquidCrystal_I2C _lcd = LiquidCrystal_I2C(0x27, 20, 4); /** LCD Display Object */
    Window* _window; /** Pointer to Window Object */
    SystemMode* _mode; /** Pointer to System Mode Object */

    float _aperture; /** Aperture Value */
    float _temperature; /** Temperature Value */
    SystemMode::Mode _currentMode; /** Current Mode Value */

    /**
     * \brief Displays the Body of the Message
     * 
     * \param period The Period of the Task
     */
    void displayMessageBody();

    /**
     * \brief Displays the Mode Value
     * 
     * \param mode The Mode Value
     */
    void displayMode(SystemMode::Mode mode);

    /**
     * \brief Displays the Aperture Value
     * 
     * \param aperture The Aperture Value
     */
    void displayAperture(float aperture);

    /**
     * \brief Displays the Temperature Value
     * 
     * \param temperature The Temperature Value
     */
    void displayTemperature(float temperature);
};