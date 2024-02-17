#ifndef DATE
#define DATE

#include <string>

class Date {
    // attributes
    private:
        int month;
        int day;
        int year;
    
    // methods
    public:
        Date(int m, int d, int y);
        std::string FormatToTimestamp(); 
};

#endif
