#ifndef HELPER_HPP
#define HELPER_HPP

#include <fstream>

class Helper {

    public:

        std::string validMonths[24] = { "january",
                                    "January",
                                    "february",
                                    "February",
                                    "march",
                                    "March",
                                    "april",
                                    "April",
                                    "may",
                                    "May",
                                    "june",
                                    "June",
                                    "july",
                                    "July",
                                    "august",
                                    "August",
                                    "september",
                                    "September",
                                    "october",
                                    "October",
                                    "november",
                                    "November",
                                    "december",
                                    "December" };
        std::string expenses [20];
        std::string expense;
        int numExpenses;
        std::string username;
        std::string dataFilesPath;
        std::string reportFilesPath;
        std::string month;
        std::ifstream inputFile;
        std::ofstream outputFile;
        
};

#endif