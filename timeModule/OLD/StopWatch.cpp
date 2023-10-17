#include "StopWatch.h"

std::vector<int> StopWatch::getElapsedTimeComponents() {
    std::vector<int> timeComponents = {hour, minute, second};
    return timeComponents;
}

std::vector<int> StopWatch::addSecond(){
    second++;

    if(second >= 60){
        second -= 60;
        minute++;
    } 
            
    if(minute >= 60){
        minute -= 60;
        hour++;
    }

    return getElapsedTimeComponents();
}

void StopWatch::reset(){
    hour = 0;
    minute = 0;
    second = 0;
    isActive = false;
}