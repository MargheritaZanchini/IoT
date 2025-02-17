#pragma once

#include "../tasks/Task.h"
#include "../communication/SerialHandler.h"
#include "../components/logical/Window.h"
#include "../components/logical/SystemManager.h"

/**
 * \brief Door Task Class
 * \implements{Task}
 */
class WindowTask : public Task {   
public:
    /**
     * \brief Creates New Door Task
     * \param window Pointer to Door Object
     */
    WindowTask(Window* window, SystemManager* mode);

    void tick() override;

private:
    Window* _window; /** Pointer to Door Object */
    SystemManager* _mode; /** Pointer to System Mode Object */
};