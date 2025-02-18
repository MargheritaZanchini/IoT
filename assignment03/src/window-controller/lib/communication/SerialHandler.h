#pragma once

#include <Arduino.h>

#include "../components/logical/SystemManager.h"

/**
 * \brief Serial Helper Object Class
 * \details Manages Serial Communication and Actions
 * \note See https://github.com/pslab-unibo/esiot-2024-2025/blob/master/Arduino/module-lab-2.2/remote_blinking/MsgService.h
 */
class SerialHelperObject {
public:
    void init();

    void setTemperature(float temperature);
    void setAperture(int aperture);
    void setMode(SystemManager::Mode mode);

    float getTemperature();
    int getAperture();
    SystemManager::Mode getMode();

private:
    bool _temperatureAvailable; /** Temperature Available Flag */
    bool _apertureAvailable; /** Aperture Available Flag */
    bool _modeAvailable; /** Mode Available Flag */

    float _temperature; /** Temperature Value */
    int _aperture; /** Aperture Value */
    SystemManager::Mode _mode; /** Current Mode */
};

extern SerialHelperObject SerialHelper; /** Global Serial Helper Object \note See SerialHandler */
