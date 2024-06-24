#include "Date.hpp"

/**
 * initializes each class attribute to 0
 */ 
Date::Date() {
    month = 0;
    day = 0;
    year = 0;
}

/**
 * initializes each class attribute based on input parameters
 * 
 * @param m a date's month
 * @param d a date's day
 * @param y a date's year
 */ 
Date::Date(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
}

/**
 * formats a Date into a timestamp EX) 09-22-2000 -> 2000-09-22 00:00:00
 * 
 * @return a string that represent's a date in timestamp format
 */ 
std::string Date::FormatToTimestamp() {
    std::stringstream ss;
        ss << std::setfill('0');
        ss << std::setw(4) << year 
           << "-" 
           << std::setw(2) << month 
           << "-" 
           << std::setw(2) << day 
           << " 00:00:00";
        return ss.str();
}

/**
 * gets the current date and instantiates a new Date object
 * 
 * @return an instantiated date object with a month, day, and year value
 */
Date Date::GetCurrentDate() {
    // get the current system time
    auto now = std::chrono::system_clock::now();
    // convert the system time to a time_t object
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    // convert the time_t object to a struct tm (broken down time)
    std::tm *tm_now = std::localtime(&time_now);
    // instantiate a new Date object
    Date date((tm_now->tm_mon + 1), tm_now->tm_mday, (tm_now->tm_year + 1900));
    
    return date;
}
