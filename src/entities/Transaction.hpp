#ifndef TRANSACTION
#define TRANSACTION

#include "../utils/Date.hpp"

#include <string>
#include <sstream>
#include <iomanip>

class Transaction {
    // attributes
    // each of these represent a column inside the Transactions table
    private:
        int id;
        int userID; 
        std::string amount;
        std::string category;
        std::string transactionDate;
    
    // methods
    public:     
        Transaction();
        Transaction(int id, std::string a, std::string c, Date td);
        
        // Getters
        int GetTransactionID();
        int GetUserID();
        std::string GetAmount();
        std::string GetDate();
        std::string GetCategory();

        // Setters
        void SetTransactionID(int transactionID);
        void SetUserID(int id);
        void SetAmount(std::string a);
        void SetCategory(std::string c);
        void SetDate(Date date);
};

#endif
