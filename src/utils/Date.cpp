#include "Date.hpp"

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
