#ifndef __A02_CONSTANTS__
#define __A02_CONSTANTS__

#include <Arduino.h>

/**
 * @brief Constants Namespace
 * 
 * Implemented for Global Arduino-Workspace Use
 */
namespace Constants {
    namespace Button {
        namespace Close {
            constexpr int PIN = 6; /** Pin Number for Close Button Digital Input */
        }
        namespace Open {
            constexpr int PIN = 7; /** Pin Number for Open Button Digital Input */
        }

        constexpr int DEBOUNCE_TIME = 100; /** Debounce Time in Milliseconds (to Prevent False Readings) */
    }

    namespace LCD {
        constexpr int ADDRESS = 0x27; /** Address of I2C LCD Display */
        constexpr int COLUMNS = 20; /** Number of Character Columns on LCD Display */
        constexpr int ROWS = 20; /** Number of Character Rows on LCD Display */

        const String MSG_DEFAULT = "Press Open to Enter Waste"; /** Press Open to Enter Waste */
        const String MSG_DOOR_OPEN = "Press Close When Done"; /** Press Close When Done */
        const String MSG_DOOR_CLOSE = "Waste Received"; /** Waste Received */
        const String MSG_CONTAINER_FULL = "Container Full"; /** Container Full */
        const String MSG_TEMPERATURE_ALARM = "Problem Detected!"; /** Problem Detected! */
    }

    namespace LED {
        namespace OK {
            constexpr int PIN = 8; /** Pin Number for Status OK LED Indicator */
        }
        namespace Error {
            constexpr int PIN = 9; /** Pin Number for Error Status LED Indicator */
        }
    }

    namespace PIR {
        constexpr int PIN = 5; /** Pin Number for Passive Infrared Motion Sensor */
        constexpr int CALIBRATION_TIME = 4000; /** Time in Seconds for the PIR to be Calibrated \see{Constants::SECOND} */
    }

    namespace Servo {
        constexpr int PIN = 2; /** Pin Number for Servo Motor Control Signal */
        constexpr int USER_DOOR_OPENED = 750; //0°
        constexpr int USER_DOOR_CLOSED = 1500; //90°
        constexpr int OPERATOR_DOOR_OPENED = 2250; //180° 
        constexpr unsigned long CLOSING_MESSAGE_TIME = 3000;
        constexpr unsigned long OPERATOR_EMPTY_TIME = 5000;
    }

    namespace Sonar {
        namespace Trigger {
            constexpr int PIN = 12;  /** Pin Number for Ultrasonic Sensor Trigger Signal */
        }
        namespace Echo {
            constexpr int PIN = 13; /** Pin Number for Ultrasonic Sensor Echo Signal */
        }
        constexpr float TEMPERATURE = 20; /** Temperature for Speed Calculation @note https://en.wikipedia.org/wiki/Speed_of_sound */
        constexpr float SOUND_VELOCITY = 331.45 + (0.62 * TEMPERATURE); /** Current Sound Velocity */
        constexpr float EMPTY_DISTANCE = 1.0; /** Empty Distance (in Meters) */
        constexpr float FULL_DISTANCE = 0.0; /** Full Distance (in Meters) */
        constexpr float FULL_THRESHOLD = 0.25*EMPTY_DISTANCE; /** Alarm Threshold (75% Full) */
    }

    namespace Thermistor {
        constexpr int PIN = A0; /** Pin Number for Thermistor Analog Input */
        constexpr int MAX_TEMPERATURE = 30; 
        constexpr int MAX_TEMPERATURE_TIME = 4000; /**If the thermistor is in MAX_TEMP for MAX_TEMP_TIME there is a problem  */
    }

    constexpr unsigned long BAUD_RATE = 9600; /** Baud Rate for Serial Communication */
}

#endif