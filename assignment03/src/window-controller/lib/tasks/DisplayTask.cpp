#include "DisplayTask.h"

#include <Arduino.h>

DisplayTask::DisplayTask(Window* window) {
    _lcd.init();
    _lcd.backlight();
    _lcd.setCursor(0, 0);

    _window = window;

    _currentMode = (SerialHelperObject::Mode) -1;
    _currentAperture = -1;
    _currentTemperature = -1;

    displayMessageBody();
}

/**
 * \brief Initializes the Task
 * 
 * Message Format:
 * - current mode (AUTOMATIC / MANUAL)
 * - current opening of the window
 * - current temperature value (MANUAL)
 */
void DisplayTask::tick() {
    SerialHelperObject::Mode newMode = SerialHelper.getMode();
    displayMode(newMode);

    int newAperture = _window->getPercentage();
    displayAperture(newAperture);

    if(newMode == SerialHelperObject::Mode::MANUAL) {
        float newTemperature = SerialHelper.getTemperature();
        displayTemperature(newTemperature);
    }
}

void DisplayTask::displayMessageBody() {
    _lcd.clear();

    _lcd.setCursor(0, 0);
    _lcd.print("Mode: ");
    
    _lcd.setCursor(0, 1);
    _lcd.print("Aperture: ");

    if(_currentMode == SerialHelperObject::Mode::MANUAL) {
        _lcd.setCursor(0, 2);
        _lcd.print("Temperature: ");
    }
}

void DisplayTask::displayMode(SerialHelperObject::Mode mode) {
    if(_currentMode == mode) {
        return;
    }

    _currentMode = mode;

    displayMessageBody(); // Se la modalità è cambiata, riscrivi il body del messaggio

    _lcd.setCursor(13, 0);
    _lcd.print(DISPLAY_CLEARING_STRING);
    _lcd.setCursor(13, 0);
    
    if(_currentMode == SerialHelperObject::Mode::MANUAL) {
        _lcd.print("MANUAL");
    }
    else if(_currentMode == SerialHelperObject::Mode::AUTOMATIC) {
        _lcd.print("AUTO");
    }
    else {
        _lcd.print("N/A");
    }
}

void DisplayTask::displayAperture(int aperture) {
    if(_currentAperture == aperture) {
        return;
    }

    _currentAperture = aperture;

    _lcd.setCursor(13, 1);
    _lcd.print(DISPLAY_CLEARING_STRING);

    _lcd.setCursor(13, 1);

    String apertureMessage = "";

    if(_currentAperture < 0 || _currentAperture > 100) {
        apertureMessage = String("N/A");
    } else {
        apertureMessage = String(_currentAperture);
        apertureMessage.concat("%");
    }

    _lcd.print(apertureMessage.c_str()); // c_str() NECESSARIO! Converte la stringa in un array di caratteri
}

void DisplayTask::displayTemperature(float temperature) {
    if(_currentMode == SerialHelperObject::Mode::AUTOMATIC) {
        return;
    }
    if(_currentTemperature == temperature) {
        return;
    }

    _currentTemperature = temperature;

    _lcd.setCursor(13, 2);
    _lcd.print(DISPLAY_CLEARING_STRING);

    _lcd.setCursor(13, 2);

    String temperatureMessage = "";
    if(_currentTemperature < 0) {
        temperatureMessage = String("N/A");
    } else {
        temperatureMessage = String(_currentTemperature);
        temperatureMessage.concat("^C"); // Il carattere del grado '°' non è supportato
    }

    _lcd.print(temperatureMessage.c_str()); // c_str() NECESSARIO! Converte la stringa in un array di caratteri
}
