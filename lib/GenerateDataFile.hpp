#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#pragma once

class GenerateDataFile {

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
        std::string lines [3];
        std::string expense;
        int numExpenses;
        std::string month;
        std::string dataFilesPath;
        std::string dataFilename;
        std::ifstream inputFile;
        std::ofstream outFile;

        GenerateDataFile();
        void Generate();
        void Prompt();
        bool ValidateMonth();
        void GetPath();
        void GetExpenses();
        
};