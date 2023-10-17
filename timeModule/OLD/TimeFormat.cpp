#include "TimeFormat.h"

std::string formatTime(int hour, int minute, int second, int millisecond, bool is12HourSystem){
    std::tm localTime;
    localTime.tm_hour = hour;
    localTime.tm_min = minute;
    localTime.tm_sec = second;

    if(!checkIfTimeIsValid(minute, second, millisecond)){
        throw InvalidTimeException("ERROR Invalid Time!");
    }
    
    if(is12HourSystem){
        char timeBuffer[15];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%I:%M:%S.", &localTime);
        std::ostringstream oss;
        oss << timeBuffer << std::setfill('0') << std::setw(3) << millisecond;
        std::strftime(timeBuffer, sizeof(timeBuffer), "%p", &localTime);
        oss << " " << timeBuffer;
        return oss.str();
    }
    else{
        char timeBuffer[30];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &localTime);
        std::ostringstream oss;
        oss << timeBuffer << ":" << std::setfill('0') << std::setw(3) << millisecond;
        return oss.str();
    }
    
}
std::string formatTime(int hour, int minute, int second, bool is12HourSystem){
    std::tm localTime;
    localTime.tm_hour = hour;
    localTime.tm_min = minute;
    localTime.tm_sec = second;
    
        if(!checkIfTimeIsValid(minute, second, 0)){
        throw InvalidTimeException("ERROR Invalid Time!");
    }

    if(is12HourSystem){
        char timeBuffer[9];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%I:%M:%S %p", &localTime);
        return timeBuffer;
    }
    else{
        char timeBuffer[30];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &localTime);
        return timeBuffer;
    }
}

std::string formatTime(int hour, int minute, bool is12HourSystem){
    std::tm localTime;
    localTime.tm_hour = hour;
    localTime.tm_min = minute;

    if(!checkIfTimeIsValid(minute, 0, 0)){
        throw InvalidTimeException("ERROR Invalid Time!");
    }

    if(is12HourSystem){
        char timeBuffer[9];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%I:%M %p", &localTime);
        return timeBuffer;
    }
    else{
        char timeBuffer[30];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M", &localTime);
        return timeBuffer;
    }
}

std::string formatDate(int day, int month, int year, int timeFormat){
    if(!checkIfDateIsValid(day, month, year)){
        throw InvalidDateException("ERROR Invalid Date!");
    }
    std::string date;
    std::string dayS = std::to_string(day);
    std::string monthS = std::to_string(month);
    std::string yearS = std::to_string(year);
    switch (timeFormat){
        case US:
            date = monthS + '/' + dayS + '/' + yearS;
        break;
        case ISO:
            date = yearS + '/' + monthS + '/' + dayS;
        break;
        default:
            date = dayS + '/' + monthS + '/' + yearS;
        break;
    }
    return date;
        
}
std::string formatDateUnsecure(int day, int month, int year, int timeFormat){
    std::string date;
    std::string dayS = std::to_string(day);
    std::string monthS = std::to_string(month);
    std::string yearS = std::to_string(year);
    switch (timeFormat){
        case US:
            date = monthS + '/' + dayS + '/' + yearS;
        break;
        case ISO:
            date = yearS + '/' + monthS + '/' + dayS;
        break;
        default:
            date = dayS + '/' + monthS + '/' + yearS;
        break;
    }
    return date;
}

std::string formatDateUnsecure(int day, int month, int timeFormat){
    std::string date;
    std::string dayS = std::to_string(day);
    std::string monthS = std::to_string(month);
    switch (timeFormat){
        case US:
            date = monthS + '/' + dayS;
        break;
        case ISO:
            date = monthS + '/' + dayS;
        break;
        default:
            date = dayS + '/' + monthS;
        break;
    }
    return date;
}

bool checkIfDateIsValid(int day, int month, int year){
    return (year > 0 && day > 0 && day <= getDaysInMonth(month, isLeapYear(year)));
}

bool isLeapYear(int year){
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool checkIfTimeIsValid(int minute, int second, int millisecond){
    return (IS_MINUTE_VALID(minute) && IS_SECOND_VALID(second) && IS_MILLISECONDS_VALID(millisecond));
}

int getDaysInMonth(int month, bool isLeapYear) {
    if(month > 0 && month < 12){
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(month == Month::FEBRUARY && isLeapYear){
            return daysInMonth[month] + 1;
        }
        return daysInMonth[month];
    }
    return 0;
}