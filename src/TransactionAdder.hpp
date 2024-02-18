#ifndef TRANSACTION_ADDER_HPP
#define TRANSACTION_ADDER_HPP

#include "utils/Helper.hpp"

class TransactionAdder : public Helper {

    public:

        std::string newTransactions [50];
        int numNewTransactions;
    
    public:

        TransactionAdder();
        void Add();
        void GetNewTransactions();
        bool ValidateNewTransactions();
        void Write();

};

#endif