#pragma once

/**
 * \brief Task Class
 */
class Task {
public:
    /**
     * \brief Pure Virtual Method; Defines the Task's Behavior
     */
    virtual void tick() = 0;
};
