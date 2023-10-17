#pragma once
#include <cstring>
#include <string>
#include <iomanip>
#include <ctime>
#include "timeMacros.h"
#include "TimeEnum.h"
#include "TimeError.h"

//Function Macros

std::string formatTime(int hour, int minute, int second, int millisecond, bool is12HourSystem);
std::string formatTime(int hour, int minute, int second, bool is12HourSystem);
std::string formatTime(int hour, int minute, bool is12HourSystem);

std::string formatDate(int day, int month, int year, int timeFormat);
std::string formatDateUnsecure(int day, int month, int timeFormat);
std::string formatDateUnsecure(int day, int month, int year, int timeFormat);


std::string formatTimeTo12HourFormat();
std::string formatTimeTo24HourFormat();
std::string formatTimeWithDayTo12HourFormat();
std::string formatTimeWithdayTo24HourFormat();

bool checkIfTimeIsValid(int minute, int second, int millisecond);
bool checkIfDateIsValid(int day, int month, int year);
int getDaysInMonth(int month, bool isLeapYear);
bool isLeapYear(int year);