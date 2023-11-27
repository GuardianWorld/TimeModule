#pragma once

#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include "TimeEnum.hpp"

class TimeThread {
    
private:
    std::chrono::time_point<std::chrono::system_clock> current_time;
    std::chrono::time_point<std::chrono::system_clock> startup_time;


    //Tick System
    unsigned int time_update_interval;
    unsigned long long int tick_counter;         
    unsigned long long int previous_update_tick;
    int tick_delay;

    //Thread and Loop
    std::thread clock_thread;
    bool is_running;

    DayOfWeek day_of_week;

    //Day/Month/Year.
    int day;
    int month;
    int year;

    int hour;
    int minute;
    int second;
    int millisecond;

    DateType date_format;
    HourType hour_format;
    bool human_simplified;

    void update_time_data(){
        current_time = std::chrono::system_clock::now();
        
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();
        std::time_t now_t = std::chrono::system_clock::to_time_t(current_time);
        std::tm* now_tm = std::localtime(&now_t);

        day_of_week = static_cast<DayOfWeek>(now_tm->tm_wday);

        year = now_tm->tm_year + 1900;
        month = now_tm->tm_mon + 1;
        day = now_tm->tm_mday;
        hour = now_tm->tm_hour;
        minute = now_tm->tm_min;
        second = now_tm->tm_sec;
        millisecond = milliseconds % 1000;
    }

    void time_update(){
        if(tick_counter >= previous_update_tick + tick_delay){
            update_time_data();
            previous_update_tick = tick_counter;
        }
    }

    void initializing_routine(){
        time_update_interval = 150;
        tick_counter = 0;
        previous_update_tick = 0;
        tick_delay = 2;
        startup_time = std::chrono::system_clock::now();
        current_time = startup_time;
        date_format = DateType::ISO;
        hour_format = HourType::H24;
        human_simplified = true;
        update_time_data();
    }

public:

    TimeThread() : is_running(true) {
        initializing_routine();

        clock_thread = std::thread([this]() {
            while (is_running) {
                tick_counter++;
                std::this_thread::sleep_for(std::chrono::milliseconds(time_update_interval));
                time_update();
            }
        });
    }

    ~TimeThread() {
        is_running = false;
        clock_thread.join();
    }

    static TimeThread& getInstance() {
        static TimeThread instance;
        return instance;
    }

    //GETS
    unsigned long long int get_ticks() {
        return tick_counter;
    }

    int get_time_update_interval(){
        return time_update_interval;
    }

    unsigned long long int get_tick_delay() {
        return tick_delay;
    }

    int get_day()   const { return day;   }
    int get_month() const { return month; }
    int get_year()  const { return year;  }

    int get_hour()          const { return hour;        }
    int get_minute()        const { return minute;      }
    int get_second()        const { return second;      }
    int get_millisecond()   const { return millisecond; }

    bool get_human_simplified() { return human_simplified; }

    DateType get_date_format(){ return date_format; }
    HourType get_hour_format(){ return hour_format; }

    //Set
    void set_time_update_interval(int new_value){
        const int time_update_upper_limit = 500;
        const int time_update_lower_limit = 50;

        this->time_update_interval = std::clamp(new_value, time_update_lower_limit, time_update_upper_limit);
    }

    void set_tick_delay(int new_value){
        const int tick_delay_upper_Limit = 10;
        const int tick_delay_lower_limit = 1;

        this->tick_delay = std::clamp(new_value, tick_delay_lower_limit, tick_delay_upper_Limit);
    }

    void set_date_format(int new_value){
        this->date_format = static_cast<DateType>(new_value);
    }

    void set_hour_format(int new_value){
        this->hour_format = static_cast<HourType>(new_value);
    }

    void set_human_simplified(bool new_value){
        human_simplified = new_value;
    }

    std::vector<long> get_elapsed_time_components(){
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - startup_time);

        // Extract the elapsed time in hours, minutes, seconds, and milliseconds
        auto elapsed_ms = elapsed_time.count();
        auto elapsed_hours = elapsed_ms / (1000 * 60 * 60);
        elapsed_ms %= (1000 * 60 * 60);

        auto elapsed_minutes = elapsed_ms / (1000 * 60);
        elapsed_ms %= (1000 * 60);
        
        auto elapsed_seconds = elapsed_ms / 1000;
        elapsed_ms = elapsed_ms % 1000;

        std::vector<long> time_components = {elapsed_hours, elapsed_minutes, elapsed_seconds, elapsed_ms};
        return time_components;
    }

    DayOfWeek get_day_of_week(){
        return day_of_week;
    }

};