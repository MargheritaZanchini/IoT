#pragma once

#define MAX_TASKS 10

#include "Task.h"

/**
 * \brief Scheduler Class
 * \author Alessandro Ricci \note See https://github.com/aricci303/
 */
class Scheduler {
public:
    void init(int basePeriod);
    virtual bool addTask(Task* task);
    virtual void schedule();

private:
    int basePeriod;
    int nTasks;
    Task* taskList[MAX_TASKS];
};
