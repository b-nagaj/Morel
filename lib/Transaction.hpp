#ifndef TRANSACTION
#define TRANSACTION

#include <string>

#include "Date.hpp"

class Transaction {
    // attributes
    // each of these represent a column inside the Transactions table
    private:
        int userID; 
        std::string amount;
        std::string category;
        std::string transactionDate;
    
    // methods
    public:
        Transaction(int id, std::string a, std::string c, Date td);
        std::string GetTransactionDate();
        void SetTransactionDate(Date date);
        int GetUserID();
        void SetUserID(int id);
        std::string GetAmount();
        void SetAmount(std::string a);
        std::string GetCategory();
        void SetCategory(std::string c);
};

#endif
