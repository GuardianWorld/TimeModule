#ifndef TIMEENUM_HPP
#define TIMEENUM_HPP

enum DayOfWeek{
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY, 
    SATURDAY
};

enum Month {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

enum DateType{
    DMY,
    MDY,
    ISO
};

enum HourType{
    H12,
    H24
};


#endif