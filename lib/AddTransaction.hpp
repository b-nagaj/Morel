#ifndef ADD_TRANSACTION_HPP
#define ADD_TRANSACTION_HPP

#include "Helper.hpp"

class AddTransaction : public Helper {

    public:

        std::string newTransactions [50];
        std::string transaction;
        std::string expenseName;
        int numNewTransactions;
        std::string dataFilename;

        AddTransaction();
        void Add();
        //void Prompt();
        void GetMonth();
        void GetExpenseName();
        bool ValidateExpenseName();
        void GetNewTransactions();
        bool ValidateNewTransactions();
        void Write();

};

#endif