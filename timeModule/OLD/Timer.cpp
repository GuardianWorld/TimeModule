#include "Timer.h"

bool Timer::checkIfTimerIsZero(){
        
    return (timerHour == 0 && 
            timerMinute == 0 &&
            timerSecond == 0);
}

std::vector<int> Timer::getTimeComponents(){
    std::vector<int> timeComponents = { getHour(), getMinute(), getSecond() };
    return timeComponents;
}

bool Timer::lowerSecond(){            

    if(checkIfTimerIsZero())
        return true;

    timerSecond--;

    if(timerSecond < 0){
        timerMinute--;
        if(timerMinute < 0){
            timerHour--;
            if(timerHour < 0){
                timerHour = 0;
            }
            timerMinute = 59;
        }
        timerSecond = 59;
    }

    return false;
}