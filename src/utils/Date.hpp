#ifndef DATE
#define DATE

#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>

class Date {
    // attributes
    private:
        int month;
        int day;
        int year;
    
    // methods
    public:
        Date();
        Date(int m, int d, int y);
        std::string FormatToTimestamp(); 
        Date GetCurrentDate();
};

#endif
