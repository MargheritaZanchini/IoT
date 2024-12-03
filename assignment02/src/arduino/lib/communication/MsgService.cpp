#include "Arduino.h"
#include "MsgService.h"

String content;

MsgServiceClass MsgService;

bool MsgServiceClass::emptyActionAvailable() {
    return hasEmptyAction;
}

bool MsgServiceClass::restoreActionAvailable() {
    return hasRestoreAction;
}

Msg* MsgServiceClass::receiveMessage() {
    if(hasEmptyAction) hasEmptyAction = false;
    else if(hasRestoreAction) hasRestoreAction = false;
    else return NULL;

    return MsgService.currentMsg;
}

void MsgServiceClass::init() {
    content.reserve(256);
    content = "";
    currentMsg = NULL;
}

// void MsgServiceClass::sendMsg(const String& msg){
//     Serial.println(msg);
// }

/**
 * @overload
 * @brief Function Called Whenever a new Message is Available (in the Serial Port).
 * @brief Uses '10' (\n) and '13' (\r) as EOS (End of String) characters.
 */
void serialEvent() {
    while (Serial.available()) {
        char ch = (char) Serial.read();

        if (ch == 10 || ch == 0 || ch == 13) {
            if(content == "[Action:Empty]") {
                MsgService.currentMsg = new Msg(content);
                MsgService.hasEmptyAction = true;
            }
            else if(content == "[Action:Restore]") {
                MsgService.currentMsg = new Msg(content);
                MsgService.hasRestoreAction = true;
            }
        }
        else content += ch;
    }

    content = "";
}