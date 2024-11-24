#ifndef __LED__
#define __LED__

class Led {
public:
    Led() = default;
    Led(int pin);
    void on();
    void off();
    void toggle();

private:
    int _pin;
};

#endif