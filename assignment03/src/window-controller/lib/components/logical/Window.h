#pragma once

#include <Arduino.h>

#include "../../src/config.h"
#include "./physical/ServoMotor.h"

/**
 * \brief Door Component Helper Class
 */
class Window {
public:
    /**
     * \brief Creates New Door Controller
     * \param servoMotor Reference to a ServoMotor Object
     */
    Window(ServoMotor* servoMotor);

    /**
     * \brief Sets the Door Position
     * \param angle Target Angle in Degrees
     */
    void setWindowAperture(int angle);

    /**
     * \brief Gets the Current Door Position
     * \return Current Angle in Degrees
     */
    int getDoorPosition();

    /**
     * \brief Checks if the Door is Open
     * \return True if the Door is Open, False Otherwise
     */
    bool isOpen();

private:
    ServoMotor* _servoMotor; /** Reference to the ServoMotor Object */
    int _angle; /** Current Angle of the Door */
};