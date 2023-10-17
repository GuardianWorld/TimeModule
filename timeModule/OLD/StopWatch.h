#pragma once
#include <chrono>
#include <string>
#include <vector>
#include "timeMacros.h"

class StopWatch{
    private:
        int hour;
        int minute;
        int second;
        bool isActive;
    public:
        
        StopWatch(){
            reset();
        }

        bool getActive(){
            return isActive;
        }

        void setActive(bool active){
            isActive = active;
        }

        std::vector<int> addSecond();
        void reset();
        std::vector<int> getElapsedTimeComponents();
};