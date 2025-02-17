#pragma once

#define CONFIG_SERIAL_BAUD_RATE 115200 /** Serial Baud Rate */

#define CONFIG_BUTTON_PIN 6 /** Button Pin Number */
#define CONFIG_DEBOUNCE_TIME 50 /** Debounce Time for Button Press */

#define CONFIG_POTENTIOMETER_PIN A0 /** Potentiometer Pin Number */
#define CONFIG_WINDOW_CLOSED 750 /** Closed Window Angle (0°) */
#define CONFIG_WINDOW_OPEN 1125 /** Open Window Angle (90°) */
#define CONFIG_SERVO_PIN 3 /** Servo Motor Pin Number */

#define AUTOMATIC_MODE 0 /** Automatic Mode */
#define MANUAL_MODE 1 /** Manual Mode */