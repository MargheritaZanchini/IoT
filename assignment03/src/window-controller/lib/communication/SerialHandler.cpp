#include "SerialHandler.h"

String content; /** Serial Content Buffer */

SerialHelperObject SerialHelper; /** Global Serial Helper Object */

/**
 * \brief Initializes the Serial Helper Object
 */
void SerialHelperObject::init() {
    content.reserve(256);
    content = "";

    _mode = SerialHelperObject::Mode::AUTOMATIC;
    _temperature = 0.0f;
    _aperture = 0;
}

/**
 * \brief Gets the Current Temperature Value
 */
float SerialHelperObject::getTemperature() {
    if(_temperatureAvailable) {
        _temperatureAvailable = false;
        return _temperature;
    }

    return -1.0f;
}

/**
 * \brief Gets the Current Window Aperture Value
 */
int SerialHelperObject::getAperture() {
    if(_apertureAvailable) {
        _apertureAvailable = false;
        return _aperture;
    }

    return -1;
}

/**
 * \brief Gets the Current System Mode
 */
SerialHelperObject::Mode SerialHelperObject::getMode() {
    return _mode;
}

/**
 * \brief Sets the Temperature Value
 */ 
void SerialHelperObject::receiveTemperature(float temperature) {
    _temperature = temperature;
    _temperatureAvailable = true;
}

/**
 * \brief Sets the Window Aperture Value
 */
void SerialHelperObject::receiveAperture(int aperture) {
    setAperture(aperture);
    _apertureAvailable = true;
}

/**
 * \brief Sets the Window Aperture Value
 */
void SerialHelperObject::setAperture(int aperture) {
    _aperture = aperture;
}

/**
 * \brief Sets the System Mode
 */
void SerialHelperObject::receiveMode(SerialHelperObject::Mode mode) {
    _mode = mode;
    _modeAvailable = true;
}

/**
 * \brief Sends a Message to the Serial Port
 */
void SerialHelperObject::sendAperture() {
    Serial.print("aperture:");
    Serial.println(_aperture);
}

/**
 * \brief Sends a Message to the Serial Port
 */
void SerialHelperObject::sendMode() {
    Serial.print("mode:");
    if(_mode == Mode::MANUAL) {
        Serial.println("manual");
    }
    else if(_mode == Mode::AUTOMATIC) {
        Serial.println("automatic");
    }
}

/**
 * \brief Switches the System Mode
 */
void SerialHelperObject::switchMode() {
    if(_mode == SerialHelperObject::Mode::AUTOMATIC) {
        _mode = SerialHelperObject::Mode::MANUAL;
    }
    else {
        _mode = SerialHelperObject::Mode::AUTOMATIC;
    }
}

/**
 * \brief [Override] Function Called Whenever a New Message is Available (in the Serial Port).
 * 
 * \brief Uses '10' (\n) and '13' (\r) as EOS (End of String) Characters.
 */
void serialEvent() {
    content = "";

    while(Serial.available()) {
        char ch = (char) Serial.read();

        if(ch == 10 || ch == 0 || ch == 13) {
            if(content.startsWith("temperature:")) {
                SerialHelper.receiveTemperature(content.substring(12).toFloat());
                content = "";
            }
            else if(content.startsWith("mode:")) {
                String mode = content.substring(5);
                mode.toLowerCase();

                if(mode == "manual") {
                    SerialHelper.receiveMode(SerialHelperObject::Mode::MANUAL);
                }
                else if(mode == "automatic") {
                    SerialHelper.receiveMode(SerialHelperObject::Mode::AUTOMATIC);
                }
                else {
                    Serial.print("Invalid Mode: ");
                    Serial.println(mode);
                }

                content = "";
            }
            else if(content.startsWith("aperture:")) {
                SerialHelper.receiveAperture(content.substring(9).toInt());
                content = "";
            }
        }
        else {
            content += ch;
        }
    }
}
