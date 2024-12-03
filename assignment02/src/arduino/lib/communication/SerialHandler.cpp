#include "Arduino.h"
#include "SerialHandler.h"

String content; /** Serial Content Buffer */

SerialHelperObject SerialHelper; /** Global Serial Helper Object */

bool SerialHelperObject::emptyActionAvailable() {
    if (SerialHelper.hasEmptyAction) {
        SerialHelper.hasEmptyAction = false;
        return true;
    }
    return false;
}

bool SerialHelperObject::restoreActionAvailable() {
    if (SerialHelper.hasRestoreAction) {
        SerialHelper.hasRestoreAction = false;
        return true;
    }
    return false;
}

void SerialHelperObject::init() {
    content.reserve(256);
    content = "";
}

/**
 * @brief [Override] Function Called Whenever a New Message is Available (in the Serial Port).
 * 
 * @brief Uses '10' (\n) and '13' (\r) as EOS (End of String) Characters.
 */
void serialEvent() {
    content = "";

    while (Serial.available()) {
        char ch = (char)Serial.read();

        if (ch == 10 || ch == 0 || ch == 13) {
            if (content == "[Action:Empty]") {
                SerialHelper.hasEmptyAction = true;
            } else if (content == "[Action:Restore]") {
                SerialHelper.hasRestoreAction = true;
            }
        } else {
            content += ch;
        }
    }
}