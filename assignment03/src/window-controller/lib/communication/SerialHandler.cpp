#include "SerialHandler.h"

String content; /** Serial Content Buffer */

SerialHelperObject SerialHelper; /** Global Serial Helper Object */

/**
 * \brief Initializes the Serial Helper Object
 */
void SerialHelperObject::init() {
    content.reserve(256);
    content = "";
}

/**
 * \brief [Override] Function Called Whenever a New Message is Available (in the Serial Port).
 * 
 * \brief Uses '10' (\n) and '13' (\r) as EOS (End of String) Characters.
 */
void serialEvent() {
    content = "";

    while(Serial.available()) {
        char ch = (char) Serial.read();

        if (ch == 10 || ch == 0 || ch == 13) {
            if(content.startsWith("aperture:")) {
                SerialHelper.aperture = content.substring(9).toFloat();
            }
            else if(content.startsWith("mode:")) {
                String mode = content.substring(5);
            }
        }
        else {
            content += ch;
        }
    }
}
