#pragma once
#include <chrono>
#include <string>
#include <vector>
#include "timeMacros.h"

class AlarmClock{
    private:
        std::string alarmName;
        int alarmHour;
        int alarmMinute;
        bool isActive;

        void setHour(int hour){
            if(IS_HOUR_VALID(hour))
                alarmHour = hour;
        }
        void setMinute(int minute){
            if(IS_MINUTE_VALID(minute))
                alarmMinute = minute;
        }

        std::vector<int> checkAlarmDuration(int currentHour, int currentMinute);

    public:
        AlarmClock(){
            alarmHour = 0;
            alarmMinute = 0;
            alarmName = "";
            isActive = false;
        }
        void setActive(bool active){
            isActive = active;
        }
        void setName(std::string name){
            alarmName = name;
        }
        bool getActive(){
            return isActive;
        } 

        std::vector<int> setTimerGetDuration(int hour, int minute ,int currentHour, int currentMinute){
            setHour(hour);
            setMinute(minute);
            setActive(true);
            return checkAlarmDuration(currentHour, currentMinute);
        }

        bool checkIfAlarmTimeIsZero(int currentHour, int currentMinute){
            std::vector<int> alarmVariables = checkAlarmDuration(currentHour, currentMinute);
            return (alarmVariables[0] == 0 && alarmVariables[1] == 0);
        }


        


};