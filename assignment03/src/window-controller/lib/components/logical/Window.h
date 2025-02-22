#pragma once

#include <Arduino.h>

#include "../../src/config.h"
#include "./physical/ServoMotor.h"

/**
 * \brief Window Component Helper Class
 */
class Window {
public:
    /**
     * \brief Creates New Window Controller
     * \param servoMotor Reference to a ServoMotor Object
     */
    Window(ServoMotor* servoMotor);

    /**
     * \brief Sets the Window Aperture
     * \param aperture Target Aperture in Degrees
     */
    void setWindowAperture(int aperture);

    /**
     * \brief Gets the Current Window Aperture
     * \return Current Aperture in Degrees
     */
    int getWindowAperture();

    /**
     * \brief Gets the Current Window Aperture Percentage
     * \return Current Percentage
     */
    int getPercentage();

    /**
     * \brief Checks if the Window is Open
     * \return True if the Window is Open, False Otherwise
     */
    bool isOpen();

private:
    ServoMotor* _servoMotor; /** Reference to the ServoMotor Object */
    int _aperture; /** Current aperture of the Window */
    int _percentage; /** Current Percentage of the Window */
};