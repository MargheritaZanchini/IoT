#ifndef __LED__
#define __LED__

class Led {
public:
    Led(int pin);
    void on();
    void off();
    void toggle();
    bool isOn() const;

private:
    int _pin;
    bool _isOn;
};

#endif