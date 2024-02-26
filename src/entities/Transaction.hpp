#ifndef TRANSACTION
#define TRANSACTION

#include <string>
#include <sstream>
#include <iomanip>

#include "../utils/Date.hpp"

class Transaction {
    // attributes
    // each of these represent a column inside the Transactions table
    private:
        int userID; 
        std::string amount;
        std::string category;
        std::string transactionDate;
    
    // methods
    private:
        // Setters
        void SetUserID(int id);
        void SetAmount(std::string a);
        void SetCategory(std::string c);
        void SetTransactionDate(Date date);

    public:     
        Transaction();
        Transaction(int id, std::string a, std::string c, Date td);
        
        // Getters
        int GetUserID();
        std::string GetAmount();
        std::string GetTransactionDate();
        std::string GetCategory();
};

#endif
