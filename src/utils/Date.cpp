#include "Date.hpp"

Date::Date(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
}

std::string Date::FormatToTimestamp() {
    std::stringstream ss;
        ss << std::setfill('0');
        ss << std::setw(4) << year << "-" << std::setw(2) << month << "-" << std::setw(2) << day << " 00:00:00";
        return ss.str();
}
