#ifndef __BUTTON__
#define __BUTTON__

#define BUTTON_DEBOUNCE_TIME 100

class Button {
public:
    Button(int pin);
    bool isPressed();

private:
    int _pin;
    long _previous;
    bool _state;
};

#endif