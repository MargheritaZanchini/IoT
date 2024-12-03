#pragma once

#include "arduino/lib/Constants.h"
#include "arduino/lib/tasks/Task.h"

/**
 * @brief Scheduler Class
 * @author Alessandro Ricci @see{https://github.com/aricci303/}
 */
class Scheduler {
public:
    void init(int basePeriod);
    virtual bool addTask(Task* task);
    virtual void schedule();

private:
    int basePeriod;
    int nTasks;
    Task* taskList[Constants::MAX_TASKS];
};
