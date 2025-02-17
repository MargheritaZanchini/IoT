#include "DisplayTask.h"

#include <Arduino.h>

DisplayTask::DisplayTask(Window* window, SystemMode* mode) {
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
    randomSeed(0);
    float aperture_test = random(0, 100);
    float temperature_test = random(20, 50);

    displayMode(_mode->getMode());
    displayAperture(aperture_test);
    displayTemperature(temperature_test);
}

void DisplayTask::displayMessageBody() {
    _lcd.clear();

    _lcd.setCursor(0, 0);
    _lcd.print("Mode: ");
    
    _lcd.setCursor(0, 1);
    _lcd.print("Aperture: ");

    if(_currentMode == SystemMode::MANUAL) {
        _lcd.setCursor(0, 2);
        _lcd.print("Temperature: ");
    }
}

void DisplayTask::displayMode(SystemMode::Mode mode) {
    if(_currentMode == mode) {
        return;
    }

    _currentMode = mode;

    displayMessageBody(); // Se la modalità è cambiata, riscrivi il body del messaggio

    _lcd.setCursor(13, 0);
    _lcd.print(DISPLAY_CLEARING_STRING);
    _lcd.setCursor(13, 0);
    _lcd.print(_currentMode == SystemMode::MANUAL ? "MANUAL" : "AUTO");
}

void DisplayTask::displayAperture(float aperture) {
    if(_aperture == aperture) {
        return;
    }

    _aperture = aperture;

    _lcd.setCursor(13, 1);
    _lcd.print(DISPLAY_CLEARING_STRING);

    _lcd.setCursor(13, 1);

    String apertureMessage = String(_aperture);
    apertureMessage.concat("%");

    _lcd.print(apertureMessage.c_str()); // c_str() NECESSARIO! Converte la stringa in un array di caratteri
}

void DisplayTask::displayTemperature(float temperature) {
    if(_temperature == temperature || _currentMode == SystemMode::AUTOMATIC) {
        return;
    }

    _temperature = temperature;

    _lcd.setCursor(13, 2);
    _lcd.print(DISPLAY_CLEARING_STRING);

    _lcd.setCursor(13, 2);

    String temperatureMessage = String(_temperature);
    temperatureMessage.concat("^C"); // Il carattere del grado '°' non è supportato

    _lcd.print(temperatureMessage.c_str()); // c_str() NECESSARIO! Converte la stringa in un array di caratteri
}
