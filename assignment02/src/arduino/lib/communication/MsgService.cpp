#include "Arduino.h"
#include "MsgService.h"

String content;

MsgServiceClass MsgService;

bool MsgServiceClass::isMsgAvailable(){
    return msgAvailable;
}

Msg* MsgServiceClass::receiveMsg(){
    if (msgAvailable){
      Msg* msg = currentMsg;
      msgAvailable = false;
      currentMsg = NULL;
      content = "";
      return msg;
    }
    else {
        return NULL; 
    }
}

void MsgServiceClass::init(){
    content.reserve(256);
    content = "";
    currentMsg = NULL;
    msgAvailable = false;  
}

void MsgServiceClass::sendMsg(const String& msg){
    Serial.println(msg);  
}

/**
 * @overload
 * @brief Function Called Whenever a new Message is Available (in the Serial Port).
 * @brief Uses '10' (\n) and '13' (\r) as EOS (End of String) characters.
 */
void serialEvent() {
    while (Serial.available()) {
        char ch = (char) Serial.read();

        if (ch == 10 || ch == 0 || ch == 13) {
            MsgService.currentMsg = new Msg(content);
            MsgService.msgAvailable = true;
        }
        else content += ch;
    }
}

bool MsgServiceClass::isMsgAvailable(Pattern& pattern){
  return (msgAvailable && pattern.match(*currentMsg));
}

Msg* MsgServiceClass::receiveMsg(Pattern& pattern){
    if (msgAvailable && pattern.match(*currentMsg)){
        Msg* msg = currentMsg;
        msgAvailable = false;
        currentMsg = NULL;
        content = "";
        return msg;
    }
    else {
        return NULL; 
    }
}

