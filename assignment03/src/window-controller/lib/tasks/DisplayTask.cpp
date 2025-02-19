#include "DisplayTask.h"

#include <Arduino.h>

DisplayTask::DisplayTask(Window* window, SystemManager* mode) {
    _lcd.init();
    _lcd.backlight();
    _lcd.setCursor(0, 0);

    _window = window;

    //_mode = mode;

    _currentAperture = -1;
    _currentTemperature = -1;

    _currentMode = SystemManager::AUTOMATIC;
    SerialHelper.setMode(_currentMode);

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
    SystemManager::Mode tempMode = SerialHelper.getMode();

    if(tempMode != (SystemManager::Mode) -1) {
        _currentMode = tempMode;
    }

    displayMode(_currentMode); // displayMode(SerialHelper.getMode());

    displayAperture(SerialHelper.getAperture());

    // if(_currentMode == SystemManager::AUTOMATIC) { // if(_mode->getMode() == SystemManager::AUTOMATIC) {
    //     displayAperture(SerialHelper.getAperture());
    // }
    // else if(_currentMode == SystemManager::MANUAL) {
    //     // displayAperture(pot);
    //     displayTemperature(SerialHelper.getTemperature());
    // }
}

void DisplayTask::displayMessageBody() {
    _lcd.clear();

    _lcd.setCursor(0, 0);
    _lcd.print("Mode: ");
    
    _lcd.setCursor(0, 1);
    _lcd.print("Aperture: ");

    if(_currentMode == SystemManager::MANUAL) {
        _lcd.setCursor(0, 2);
        _lcd.print("Temperature: ");
    }
}

void DisplayTask::displayMode(SystemManager::Mode mode) {
    if(_currentMode == mode) {
        return;
    }

    displayMessageBody(); // Se la modalità è cambiata, riscrivi il body del messaggio

    _lcd.setCursor(13, 0);
    _lcd.print(DISPLAY_CLEARING_STRING);
    _lcd.setCursor(13, 0);
    _lcd.print(_currentMode == SystemManager::MANUAL ? "MANUAL" : "AUTO");
}

void DisplayTask::displayAperture(float aperture) {
    if(_currentAperture == aperture) {
        return;
    }

    _currentAperture = aperture;

    Serial.print("Current Aperture: ");
    Serial.println(_currentAperture);

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
    if(_currentTemperature == temperature || _currentMode == SystemManager::AUTOMATIC) {
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
