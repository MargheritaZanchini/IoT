#pragma once

#include <Arduino.h>

/**
 * \brief Serial Helper Object Class
 * \details Manages Serial Communication and Actions
 * \note See https://github.com/pslab-unibo/esiot-2024-2025/blob/master/Arduino/module-lab-2.2/remote_blinking/MsgService.h
 */
class SerialHelperObject {
public:
    float temperature; /** Temperature Value */    

    /**
     * \brief Initializes the Serial Helper Object
     */
    void init();

    /**
     * \brief Checks if Empty Action is Available
     * \return True if Empty Action is Available, False Otherwise
     */
    bool emptyActionAvailable();

    /**
     * \brief Checks if Restore Action is Available
     * \return True if Restore Action is Available, False Otherwise
     */
    bool restoreActionAvailable();
};

extern SerialHelperObject SerialHelper; /** Global Serial Helper Object \note See SerialHandler */
