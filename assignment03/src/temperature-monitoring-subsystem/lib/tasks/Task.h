#pragma once

#include <Arduino.h>

#include "config.h"

class Task {
public:
    /**
     * \brief Task Event Loop
     * 
     * This function should be implemented by the Tasks
     * \see{Communication}
     * \see{Monitoring}
     */
    virtual void eventLoop() = 0;
};