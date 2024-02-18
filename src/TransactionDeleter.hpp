#ifndef TRANSACTION_DELETER_HPP
#define TRANSACTION_DELETER_HPP

#include <vector>

#include "utils/Helper.hpp"

class TransactionDeleter : public Helper {

    public:

        std::string unwantedTransactions [50];
        int numUnwantedTransactions;

    public:

        TransactionDeleter();
        void Delete();
        void GetUnwantedTransactions(); 
        bool ValidateUnwantedTransactions();
        //void DisplayTransactions();
        int RemoveTransaction();
        void Write();

};

#endif