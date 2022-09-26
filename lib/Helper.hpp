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
        double expenseValues [20];
        std::string  transactions [50];
        const int NUM_VALID_MONTHS = 24;
        const int MAX_EXPENSE_SIZE = 20;
        const int MAX_TRANSACTIONS = 50;
        std::string expense;
        int numExpenses;
        int numTransactions;
        std::string username;
        std::string dataFilesPath;
        std::string reportFilesPath;
        std::string month;
        std::ifstream inputFile;
        std::ofstream outputFile;

    public: 

        void GetUsername();
        void GetPaths();
        bool ValidateMonth();
        void GetExpenses();
        void GetExistingTransactions(std::string dataFilename);

};

#endif