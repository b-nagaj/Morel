#ifndef TRANSACTION_ADDER_HPP
#define TRANSACTION_ADDER_HPP

#include "Helper.hpp"

class TransactionAdder : public Helper {

    public:

        std::string newTransactions [50];
        std::string transaction;
        std::string expenseName;
        int numNewTransactions;
        std::string dataFilename;

        TransactionAdder();
        void Add();
        void GetMonth();
        void GetExpenseName();
        bool ValidateExpenseName();
        void GetNewTransactions();
        bool ValidateNewTransactions();
        void Write();

};

#endif