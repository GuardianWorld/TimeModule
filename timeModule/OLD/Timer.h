#include <vector>
#include <chrono>
#include "timeMacros.h"

class Timer{
private:
    int timerHour;
    int timerMinute;
    int timerSecond;
    bool isActive;

    void setHour(int hour){
        timerHour = hour;
    }
    void setMinute(int minute){
        if(IS_MINUTE_VALID(minute))
            timerMinute = minute;
    }
    void setSecond(int second){
        if(IS_SECOND_VALID(second))
            timerSecond = second;
    }

    int getHour(){ return timerHour; }
    int getMinute(){ return timerMinute; }
    int getSecond(){ return timerSecond; }

public:


    Timer(int hour, int minute, int second){
        timerHour = hour;
        timerMinute = minute;
        timerSecond = second;
        isActive = true;
    }

    void setActive(bool active){ isActive = active; }
    bool getActive(){ return isActive; }

    std::vector<int> getTimeComponents();
    bool checkIfTimerIsZero();
    bool lowerSecond();
};