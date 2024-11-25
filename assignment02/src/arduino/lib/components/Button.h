#ifndef __BUTTON__
#define __BUTTON__

#define BUTTON_DEBOUNCE_TIME 100 /** Debounce Time for the Button */

/**
 * @brief Button Component Helper Class
 * @authors Marco Marrelli, Margherita Zanchini, Sofia Caberletti
 */
class Button {
public:
    /**
     * @brief Creates New Button Instance
     * @param pin Input Pin for Button Connection
     */
    Button(int pin);

    /**
     * @brief Detects Button Press with Debouncing
     * @return true if Button is Pressed, false Otherwise
     */
    bool isPressed();

private:
    int _pin; /** Pin Number for Digital Input */
    long _previous; /** Last Time Reading for Debounce */
    bool _state; /** Current Button State Cache */
};

#endif