#pragma once

#include "Task.h"
#include "../components/physical/Button.h"
#include "../components/logical/SystemMode.h"

/**
 * \brief Mode Task Class
 * 
 * This class is responsible for managing the system mode (manual / automatic).
 */
class ModeTask : public Task {
public:
    /**
     * \brief Creates New Mode Task Instance
     * \param button Button Instance
     * \param mode System Mode Instance
     */
    ModeTask(Button* button, SystemMode* mode);
    
    /**
     * \brief Initializes the Task
     */
    void tick() override;

private:
    Button* _button; /** Button Instance */
    SystemMode* _mode; /** System Mode Instance */
};