#pragma once

#include "Led.h"
#include "Thermistor.h"
#include "Communication.h"

#include "Task.h"

/**
 * \brief Monitoring Helper Class
 */
class Monitoring : public Task {
public:
    /**
     * \brief Creates New Monitoring Instance
     */
    Monitoring();

    /**
     * \brief Checks if there is a problem (temperature too high)
     * 
     * \return If there is a problem
     */
    bool hasProblem();

    /**
     * \brief Sets the problem state (turns on error LED, turns off OK LED)
     */
    void setProblem();

    /**
     * \brief Clears the problem state (turns off error LED, turns on OK LED)
     */
    void clearProblem();

    /**
     * \brief Gets the current temperature and updates the problem state
     * 
     * \return Current temperature
     */
    float getTemperature();

    /**
     * \brief Event Loop (Overriden)
     * 
     * Monitoring Event Loop
     * \see{Task}
     */
    void eventLoop() override;

private:
    Led _ok; /** OK Indicator LED */
    Led _error; /** Error Indicator LED */
    Thermistor _thermistor; /** Thermistor Sensor */

    bool _problem; /** Problem state */
};
