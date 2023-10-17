#include "AlarmClock.h"

std::vector<int> AlarmClock::checkAlarmDuration(int currentHour, int currentMinute){
    std::tm currentLocalTime;
    std::tm alarmTime;

    // Set the current hour and minute
    currentLocalTime.tm_hour = currentHour;
    currentLocalTime.tm_min = currentMinute;
    currentLocalTime.tm_sec = 0;

    alarmTime.tm_hour = alarmHour;
    alarmTime.tm_min = alarmMinute;

    // Convert the local time to a time point
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::from_time_t(std::mktime(&currentLocalTime));
    std::chrono::system_clock::time_point currentAlarmTime = std::chrono::system_clock::from_time_t(std::mktime(&alarmTime));

    // Calculate the duration between the current time point and the alarm time point
    std::chrono::duration<int> remainingDuration = std::chrono::duration_cast<std::chrono::duration<int>>(currentAlarmTime - currentTime);

    // Extract the remaining hours and minutes from the duration
    int remainingTimeHour = remainingDuration.count() / 3600;
    int remainingTimeMinute = (remainingDuration.count() % 3600) / 60;

    std::vector<int> timeComponents = {remainingTimeHour, remainingTimeMinute};
    return timeComponents;
}