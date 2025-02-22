#pragma once

/**
 * \brief Task Class
 * \author Alessandro Ricci \note See https://github.com/aricci303/
 */
class Task {
public:
    /**
     * \brief Initializes the Task with a Given Period
     * \param period The Period of the Task in Milliseconds
     */
    virtual void init(int period) {
        myPeriod = period;  
        timeElapsed = 0;
    }

    /**
     * \brief Pure Virtual Method; Defines the Task's Behavior
     */
    virtual void tick() = 0;

    /**
     * \brief Updates the Time Elapsed and Checks if the Task Should Run
     * \param basePeriod The Base Period of the Scheduler in Milliseconds
     * \return If the Task Should Run
     */
    bool updateAndCheckTime(int basePeriod) {
        timeElapsed += basePeriod;
        if(timeElapsed >= myPeriod){
            timeElapsed = 0;
            return true;
        }
        else {
            return false;
        }
    }

private:
    int myPeriod; /** The Period of the Task in Milliseconds */
    int timeElapsed; /** The Time Elapsed Since the Last Run in Milliseconds */
};
