#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"

// class Msg {
// public:
//     Msg(String content) {
//         this->_content = content;
//     }
//   
//     String getContent() {
//         return _content;
//     }
// 
// private:
//     String _content;
// };

class MsgServiceClass {
public:
    // Msg* currentMsg;

    bool hasEmptyAction = false;
    bool hasRestoreAction = false;

    void init();
    bool emptyActionAvailable();
    bool restoreActionAvailable();

    // Msg* receiveMessage();

    // void sendMsg(const String& msg);
};

extern MsgServiceClass MsgService;

#endif