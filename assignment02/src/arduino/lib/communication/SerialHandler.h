#pragma once

#include "Arduino.h"

/**
 * @brief Serial Helper Object Class
 * @details Manages Serial Communication and Actions
 */
class SerialHelperObject {
public:
    bool hasEmptyAction = false; /**< Indicates if Empty Action is Available */
    bool hasRestoreAction = false; /**< Indicates if Restore Action is Available */

    /**
     * @brief Initializes the Serial Helper Object
     */
    void init();

    /**
     * @brief Checks if Empty Action is Available
     * @return True if Empty Action is Available, False Otherwise
     */
    bool emptyActionAvailable();

    /**
     * @brief Checks if Restore Action is Available
     * @return True if Restore Action is Available, False Otherwise
     */
    bool restoreActionAvailable();
};

extern SerialHelperObject SerialHelper; /** Global Serial Helper Object @see{SerialHandler} */