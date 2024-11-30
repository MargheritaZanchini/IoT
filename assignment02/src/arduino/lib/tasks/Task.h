#ifndef __A02_TASK__
#define __A02_TASK__

class Task {
int myPeriod;
int timeElapsed;
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
        timeElapsed += basePeriod;
        if (timeElapsed >= myPeriod){
            timeElapsed = 0;
            return true;
        }
        else {
            return false; 
        }
    }
};

#endif