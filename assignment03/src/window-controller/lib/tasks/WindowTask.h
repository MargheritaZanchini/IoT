#pragma once

#include "../tasks/Task.h"
#include "../communication/SerialHandler.h"
#include "../components/logical/Window.h"
#include "../components/physical/Potentiometer.h"

/**
 * \brief Window Task Class
 * \implements{Task}
 */
class WindowTask : public Task {   
public:
    /**
     * \brief Creates New Window Task
     * \param window Pointer to Window Object
     */
    WindowTask(Window* window, Potentiometer* pot);

    void tick() override;

private:
    Window* _window; /** Pointer to Window Object */
    Potentiometer* _pot; /** Pointer to Potentiometer Object */
};