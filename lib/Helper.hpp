#ifndef HELPER_HPP
#define HELPER_HPP

#include <fstream>

class Helper {

    public:

        // Expenses
        std::string expenses [20];
        std::string expense;
        double expenseValues [20];
        double expenseValue;
        const int MAX_EXPENSE_SIZE = 20;
        int numExpenses;

        // Transactions
        std::string  transactions [50];
        std::string transaction;
        const int MAX_TRANSACTIONS = 50;
        int numTransactions;

        // Data
        std::string validMonths[24] = { "january", "January", "february", "February", "march", "March", "april", "April", "may", "May", "june", "June", "july", "July", "august", "August", "september", "September", "october", "October", "november", "November", "december", "December" };
        std::string month;
        const int NUM_VALID_MONTHS = 24;
        std::string username;
        std::string dataFilesPath;
        std::string dataFilename;
        std::ifstream inputFile;

        // Reports
        std::string reportFilesPath;
        std::string reportFilename;
        std::ofstream outputFile;

    public: 
        
        // Expenses
        void GetExpenses();

        // Transactions
        void GetExistingTransactions();
        void GetExpenseName();

        // Data
        void GetUsername();
        void GetPaths();

        // Validation
        bool ValidateMonth();
        bool ValidateExpenseName();

        // utilities
        void GetMonth();
        void Clear();

};

#endif