/*#include "TimerModule.h"

void TimerSystem::executeSystem(){
    std::vector<int> timeComponents = timeSystemReference.getCurrentTimeComponents();
    currentHour = timeComponents[0];
    currentMinute = timeComponents[1];
    if(stopWatch.getActive()){
        stopWatch.addSecond();
    }
    if(alarms.size() > 0){
        checkAlarms();
    }
}

void TimerSystem::checkAlarms(){
    for(int x = 0; x < alarms.size(); x++){
        if(alarms[x].first.getActive()){
            if(alarms[x].first.checkIfAlarmTimeIsZero(currentHour, currentMinute)){
                alarms[x].second = true;
            }
        }
    }
}*/