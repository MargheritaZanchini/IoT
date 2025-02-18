#include "DisplayTask.h"

#include <Arduino.h>

DisplayTask::DisplayTask(Window* window, SystemManager* mode) {
    _lcd.init();
    _lcd.backlight();
    _lcd.setCursor(0, 0);

    _window = window;
    _mode = mode;

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
    displayMode(SerialHelper.getMode());
    displayAperture(SerialHelper.getAperture());

    if(_mode->getMode() == SystemManager::MANUAL) {
        displayTemperature(SerialHelper.getTemperature());
    }
}

void DisplayTask::displayMessageBody() {
    _lcd.clear();

    _lcd.setCursor(0, 0);
    _lcd.print("Mode: ");
    
    _lcd.setCursor(0, 1);
    _lcd.print("Aperture: ");

    if(_mode->getMode() == SystemManager::MANUAL) {
        _lcd.setCursor(0, 2);
        _lcd.print("Temperature: ");
    }
}

void DisplayTask::displayMode(SystemManager::Mode mode) {
    if(_mode->getMode() == mode) {
        return;
    }

    _mode->setMode(mode);

    displayMessageBody(); // Se la modalità è cambiata, riscrivi il body del messaggio

    _lcd.setCursor(13, 0);
    _lcd.print(DISPLAY_CLEARING_STRING);
    _lcd.setCursor(13, 0);
    _lcd.print(_mode->getMode() == SystemManager::MANUAL ? "MANUAL" : "AUTO");
}

void DisplayTask::displayAperture(float aperture) {
    if(_currentAperture == aperture) {
        return;
    }

    _currentAperture = aperture;

    _lcd.setCursor(13, 1);
    _lcd.print(DISPLAY_CLEARING_STRING);

    _lcd.setCursor(13, 1);

    String apertureMessage = String(_currentAperture);
    apertureMessage.concat("%");

    _lcd.print(apertureMessage.c_str()); // c_str() NECESSARIO! Converte la stringa in un array di caratteri
}

void DisplayTask::displayTemperature(float temperature) {
    if(_currentTemperature == temperature || _mode->getMode() == SystemManager::AUTOMATIC) {
        return;
    }

    _currentTemperature = temperature;

    _lcd.setCursor(13, 2);
    _lcd.print(DISPLAY_CLEARING_STRING);

    _lcd.setCursor(13, 2);

    String temperatureMessage = String(_currentTemperature);
    temperatureMessage.concat("^C"); // Il carattere del grado '°' non è supportato

    _lcd.print(temperatureMessage.c_str()); // c_str() NECESSARIO! Converte la stringa in un array di caratteri
}
