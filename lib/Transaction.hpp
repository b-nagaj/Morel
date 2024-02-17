#ifndef TRANSACTION
#define TRANSACTION

#include <string>

#include "Date.hpp"

class Transaction {
    // attributes
    private:
        int userID;
        std::string amount;
        std::string category;
        std::string transactionDate;
    
    // methods
    private:
        std::string GetTransactionDate();
        void SetTransactionDate(Date date);
        int GetUserID();
        void SetUserID(int id);
        std::string GetAmount();
        void SetAmount(std::string a);
        std::string GetCategory();
        void SetCategory(std::string c);
        std::string FormatToDecimal(std::string value);
    public:
        Transaction(int id, double a, std::string c, std::string td);

};

#endif
