#ifndef ALARMCLOCK_HPP
#define ALARMCLOCK_HPP

#include <string>
#include <chrono>
#include <vector>
#include "TimeEnum.hpp"
#include "TimeError.hpp"

class AlarmClock{
private:
    std::string alarm_name;
    int alarm_hour;
    int alarm_minute;
    bool is_active;
    bool has_gone_off_today; // Add a flag
    bool activeDays[7]; // Add an array of booleans for each day of the week [0] = Sunday, [1] = Monday, etc.

public:
    AlarmClock() : alarm_name(""), is_active(false) {
        alarm_hour = 0;
        alarm_minute = 0;
    }

    AlarmClock(std::string name, int hour, int minute) : alarm_name(name), is_active(true) {
        alarm_hour = 0;
        alarm_minute = 0;
        set_hour(hour);
        set_minute(minute);
    }

    void set_active_day(DayOfWeek day_of_week, bool active) {
        activeDays[day_of_week] = active;
    }

    void set_active(bool active){
        has_gone_off_today = false;
        is_active = active;
    }

    void set_name(std::string name){
        alarm_name = name;
    }

    bool get_active(){
        return is_active;
    }

    int get_hour(){
        return alarm_hour;
    }
    
    int get_minute(){
        return alarm_minute;
    }

    std::string get_name(){
        return alarm_name;
    }

    std::vector<int> check_alarm_duration(int current_hour, int current_minute){
         std::vector<int> timeComponents;

        // Calculate the time difference in minutes
        int currentTotalMinutes = current_hour * 60 + current_minute;
        int alarmTotalMinutes = alarm_hour * 60 + alarm_minute;
        int timeDifference = alarmTotalMinutes - currentTotalMinutes;

        // Handle cases where the alarm is in the past or within the next 24 hours
        if (timeDifference < 0) {
            timeDifference += 24 * 60;  // Assuming a 24-hour clock
        }

        // Calculate the hours and minutes from the time difference
        int hours = timeDifference / 60;
        int minutes = timeDifference % 60;

        timeComponents.push_back(hours);
        timeComponents.push_back(minutes);

        return timeComponents;
    }

    std::vector<int> set_clock(int hour, int minute ,int current_hour, int current_minute){
        set_hour(hour);
        set_minute(minute);
        set_active(true);
        return check_alarm_duration(current_hour, current_minute);
    }
    
    void set_hour(int hour){
        if(hour >= 0 && hour <= 23)
            alarm_hour = hour;
    }

    void set_minute(int minute){
        if(minute >= 0 && minute < 60){
            alarm_minute = minute;
        }
    }

    bool can_go_off_today() {
        return is_active && !has_gone_off_today;
    }

    void mark_as_gone_off() {
        has_gone_off_today = true;
    }

    void reset_gone_off(DayOfWeek day_of_week) {
        if (activeDays[day_of_week] && is_active){
            has_gone_off_today = false;
        }
    }

};

#endif //ALARMCLOCK_HPP