#pragma once

#include <Arduino.h>

/**
 * \brief Serial Helper Object Class
 * \details Manages Serial Communication and Actions
 * \note See https://github.com/pslab-unibo/esiot-2024-2025/blob/master/Arduino/module-lab-2.2/remote_blinking/MsgService.h
 */
class SerialHelperObject {
public:
    enum Mode {
        MANUAL, /** Manual Mode */
        AUTOMATIC/** Automatic Mode */
    };

    void init();

    void receiveTemperature(float temperature);
    float getTemperature();
    
    void receiveAperture(int aperture);
    void setAperture(int aperture);
    int getAperture();
    void sendAperture();
    
    void receiveMode(Mode mode);
    Mode getMode();
    void sendMode();
    void switchMode();    
    
private:
    float _temperature; /** Temperature Value */
    int _aperture; /** Aperture Value */
    SerialHelperObject::Mode _mode; /** Current Mode */

    bool _temperatureAvailable; /** Temperature Available Flag */
    bool _apertureAvailable; /** Aperture Available Flag */
    bool _modeAvailable; /** Mode Available Flag */
};

extern SerialHelperObject SerialHelper; /** Global Serial Helper Object \note See SerialHandler */
