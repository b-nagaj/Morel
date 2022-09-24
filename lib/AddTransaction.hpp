#ifndef ADD_TRANSACTION_HPP
#define ADD_TRANSACTION_HPP

#include "Helper.hpp"

class AddTransaction : public Helper {

    public:

        std::string newTransactions [50];
        std::string transaction;
        int numNewTransactions;
        std::string dataFilename;

        AddTransaction();
        void Add();
        void Prompt();
        // bool ValidateExpense();
        // bool ValidateTransaction();
        void Write();

};

#endif