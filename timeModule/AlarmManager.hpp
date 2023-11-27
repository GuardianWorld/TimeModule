#ifndef ALARMMANAGER_HPP
#define ALARMMANAGER_HPP

#include <vector>
#include "AlarmClock.hpp"
#include "TimeThread.hpp"
#include "../printModule/PrintThread.hpp"

class AlarmManager{
private:
    std::vector<AlarmClock> alarms;
    TimeThread& clock;
    PrintThread& printer;
    std::thread alarmThread;
    bool isRunning;

    void alarm_thread(){
        isRunning = true;
        while(isRunning){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            check_alarms();
        }
    }
    void check_alarms() {
        for (AlarmClock& a : alarms) {
            if (a.can_go_off_today() && a.get_hour() == clock.get_hour() && a.get_minute() == clock.get_minute()) {
                std::string message = "Alarm " + a.get_name() + " is going off!\n";
                printer << message;
                a.mark_as_gone_off();
            }
        }
    }

    AlarmClock* find_alarm_by_name(const std::string& name) {
        for (auto& alarm : alarms) {
            if (alarm.get_name() == name) {
                return &alarm;
            }
        }
        return nullptr; // Return a null pointer if not found
    }

public:
    AlarmManager(TimeThread& time_clock, PrintThread& printer_thread): alarmThread([this](){alarm_thread();}), clock(time_clock), printer(printer_thread){}

    ~AlarmManager(){
        isRunning = false;
        alarmThread.join();
    }

    void add_alarm(AlarmClock alarm){
        alarms.push_back(alarm);
    }

    static AlarmClock build_alarm(std::string name, int hour, int minute){
        return AlarmClock(name, hour, minute);
    }

    void remove_alarm(std::string name){
        for(int i = 0; i < alarms.size(); i++){
            if(alarms[i].get_name() == name){
                alarms.erase(alarms.begin() + i);
                return;
            }
        }
    }

    void rename_alarm(std::string old_name, std::string new_name){
        AlarmClock* alarm = find_alarm_by_name(old_name);
        if (alarm)
            alarm->set_name(new_name);
        else
            printer << "Alarm " << old_name << " not found!\n";
    }

    void set_alarm_active(std::string name, bool active){
        AlarmClock* alarm = find_alarm_by_name(name);
        if (alarm)
            alarm->set_active(active);
        else
            printer << "Alarm " << name << " not found!\n";
    }

    void set_alarm_hour(const std::string& name, int hour) {
        AlarmClock* alarm = find_alarm_by_name(name);
        if (alarm) {
            alarm->set_hour(hour);
            return;
        }
        printer << "Alarm " << name << " not found!\n";
        
    }

    void set_alarm_minute(const std::string& name, int minute) {
        AlarmClock* alarm = find_alarm_by_name(name);
        if (alarm) {
            alarm->set_minute(minute);
            return;
        }
        printer << "Alarm " << name << " not found!\n";
    }

    void set_alarm_time(const std::string& name, int hour, int minute) {
        AlarmClock* alarm = find_alarm_by_name(name);
        if (alarm) {
            alarm->set_hour(hour);
            alarm->set_minute(minute);
            return;
        }
        printer << "Alarm " << name << " not found!\n";
    }

    void set_day_active(const std::string& name, DayOfWeek day, bool active) {
        AlarmClock* alarm = find_alarm_by_name(name);
        if (alarm) {
            alarm->set_active_day(day, active);
            return;
        }
        printer << "Alarm " << name << " not found!\n";
    }

    int get_alarm_hour(std::string name){
        AlarmClock* alarm = find_alarm_by_name(name);
        if (alarm) 
            return alarm->get_hour();
        return -1;
    }

    int get_alarm_minute(std::string name){
        AlarmClock* alarm = find_alarm_by_name(name);
        if (alarm) 
            return alarm->get_minute();
        return -1;
    }

    bool get_alarm_active(std::string name){
        AlarmClock* alarm = find_alarm_by_name(name);
        if (alarm) 
            return alarm->get_active();
        return false;
    }

    void reset_daily_flags() {
        for (AlarmClock& a : alarms) {
            a.reset_gone_off(clock.get_day_of_week());
    }
}
};
#endif