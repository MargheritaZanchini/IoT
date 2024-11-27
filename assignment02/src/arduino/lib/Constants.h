#ifndef __ASSIGNMENT_02_CONSTANTS__
#define __ASSIGNMENT_02_CONSTANTS__

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
    }

    namespace LED {
        namespace OK {
            constexpr int PIN = 6; /** Pin Number for Status OK LED Indicator */
        }
        namespace Error {
            constexpr int PIN = 7; /** Pin Number for Error Status LED Indicator */
        }
    }

    namespace PIR {
        constexpr int PIN = 5; /** Pin Number for Passive Infrared Motion Sensor */
        constexpr int CALIBRATION_TIME = 4000; /** Time in Seconds for the PIR to be Calibrated \see{Constants::SECOND} */
    }

    namespace Servo {
        constexpr int PIN = 2; /** Pin Number for Servo Motor Control Signal */
        constexpr int USER_DOOR_OPENED = 180; //90°
        constexpr int USER_DOOR_CLOSED =90; //0°
        constexpr int OPERATOR_DOOR_OPENED = 0; //-90° 
        constexpr unsigned long DELTA_T2 = 3000;
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
        constexpr float ALARM_THRESHOLD = 0.75*FULL_DISTANCE; /** Alarm Threshold (75% Full) */
    }

    namespace Thermistor {
        constexpr int PIN = A0; /** Pin Number for Thermistor Analog Input */
        constexpr int MAX_TEMPERATURE = 28; 
        constexpr int MAX_TEMPERATURE_THRESHOLD = 4000; /**If the thermistor is in MAX_TEMP for MAX_TEMP_TIME there is a problem  */
    }

    constexpr unsigned long BAUD_RATE = 9600; /** Baud Rate for Serial Communication */
}

#endif