#pragma once

#include <Arduino.h>
#include "arduino/lib/Constants.h"
#include "arduino/lib/components/physical/ServoMotor.h"

/**
 * \brief Door Component Helper Class
 */
class Door {
public:
    /**
     * \brief Creates New Door Controller
     * \param servoMotor Reference to a ServoMotor Object
     */
    Door(ServoMotor* servoMotor);

    /**
     * \brief Sets the Door Position
     * \param angle Target Angle in Degrees
     */
    void setDoorPosition(int angle);

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

    /**
     * \brief Checks if the Door is Operator Open
     * \return True if the Door is Operator Open, False Otherwise
     */
    bool isOperatorOpen();

private:
    ServoMotor* _servoMotor; /** Reference to the ServoMotor Object */
    int _angle; /** Current Angle of the Door */
};