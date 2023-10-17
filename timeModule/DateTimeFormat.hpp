#ifndef DATETIMEFORMAT_HPP
#define DATETIMEFORMAT_HPP
#include <string>
#include "TimeError.hpp"
#include "TimeThread.hpp"
#include "TimeEnum.hpp"

class DateTimeFormat {
private:
    static bool is_valid_hour(int hour, int hour_format) {
        if(hour_format == HourType::H12){
            return (hour >= 0) && (hour <= 12);
        }
        return (hour >= 0) && (hour < 24);
    }

    static bool is_valid_minute(int minute) {
        return (minute >= 0) && (minute < 60);
    }

    static bool is_valid_second(int second) {
        return (second >= 0) && (second < 60);
    }

    static bool is_valid_millisecond(int millisecond) {
        return (millisecond >= 0) && (millisecond < 1000);
    }

    static std::string build_date_string(int day, int month, int year, int timeFormat){
        switch (timeFormat){
            case DateType::MDY:
                return std::to_string(month) + '/' + std::to_string(day) + '/' + std::to_string(year);
            break;
            case DateType::ISO:
                return std::to_string(year) + '/' + std::to_string(month) + '/' + std::to_string(day);
            break;
            default:
                return std::to_string(day) + '/' + std::to_string(month) + '/' + std::to_string(year);
            break;
        }
    }

    static std::string build_time_string(int hour, int minute, int second, int millisecond, bool morning, bool human_simplified, int hour_format){
        std::string result;
        result = std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
        if(!human_simplified)
            result.append(":" + millisecond);
        if(hour_format == HourType::H12){
            if(morning)
                result.append(" AM");
            else
                result.append(" PM");

        }

        return result;
    }

public:

    /*
        Outside Date functions;
    */

    static bool is_leap_year(int year){
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    }

    static std::string format_unsecure_date(int day, int month, int year, int date_format){
        if(!check_valid_date(day, month, year)){
            throw InvalidDateException("ERROR Invalid Date!");
        }
        return build_date_string(day,month,year, date_format);
    }

     static std::string format_secure_date(int day, int month, int year, int date_format){
        return build_date_string(day,month,year, date_format);
    }

    static bool check_valid_date(int day, int month, int year){
        return (year > 0 && day > 0 && day <= get_days_in_month(month, is_leap_year(year)));
    }

    static int get_days_in_month(int month, bool is_leap_year) {
        if(month > 0 && month < 12){
            int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if(month == Month::FEBRUARY && is_leap_year){
                return days_in_month[month] + 1;
            }
            return days_in_month[month];
        }
        return 0;
    }

    /*
        Inside Date Functions;
    */

    static std::string build_internal_date_string(){
        TimeThread &instance = TimeThread::getInstance();
        int day = instance.get_day();
        int month = instance.get_month();
        int year = instance.get_year();
        DateType date_format = instance.get_date_format();

        return build_date_string(day,month,year, date_format);
    }

    /*
        Time Functions;
    */

    static bool check_valid_time(int hour, int minute, int second, int millisecond, bool morning, int hour_format){
        return (is_valid_hour(hour, hour_format) && is_valid_minute(minute) && is_valid_second(second) && is_valid_millisecond(millisecond));
    }

    static std::string format_unsecure_time(int hour, int minute, int second, int millisecond, bool morning, int hour_format){
        if(!check_valid_time(hour, minute, second, millisecond, morning, hour_format)){
            throw InvalidTimeException("ERROR Invalid Time!");
        }
        return build_time_string(hour, minute, second, millisecond, morning, false, hour_format);
    }


   /* Internal Time Functions;*/

    static std::string build_internal_time_string(){
        TimeThread &instance = TimeThread::getInstance();
        int hour = instance.get_hour();
        int minute = instance.get_minute();
        int second = instance.get_second();
        int millisecond = instance.get_millisecond();
        HourType hour_format = instance.get_hour_format();
        bool morning = instance.get_morning();
        bool human_simplified = instance.get_human_simplified();

        return build_time_string(hour, minute, second, millisecond, morning, human_simplified, hour_format);
    }



};

#endif