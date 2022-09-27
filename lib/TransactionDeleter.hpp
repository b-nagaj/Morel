#ifndef TRANSACTION_DELETER_HPP
#define TRANSACTION_DELETER_HPP

#include <vector>

#include "Helper.hpp"

class TransactionDeleter : Helper {

    public:

        std::string unwantedTransactions [50];
        std::string transaction;
        std::string expenseName;
        int numUnwantedTransactions;
        std::string dataFilename;

        TransactionDeleter();
        void Delete();
        void GetMonth();
        void GetExpenseName();
        bool ValidateExpenseName();
        void GetUnwantedTransactions(); 
        bool ValidateUnwantedTransactions();
        void DisplayTransactions();
        int RemoveTransaction();
        void Write();

};

#endif