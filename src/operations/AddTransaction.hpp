#ifndef ADD_TRANSACTION
#define ADD_TRANSACTION

#include "../utils/Date.hpp"
#include "../entities/Transaction.hpp"

class AddTransaction {
    // attributes
    private:
        int numNewTransactions;
        Transaction newTransactions [50];
        std::string transactionAmount;
        std::string transactionCategory;

    // methods
    private:  
        void GetNewTransactions();
        bool ValidateNewTransactionAmount(std::string uncheckedTransactionAmount);
        bool ValidateNewTransactionCategory(std::string uncheckedTransactionCategory);
        void AddNewTransactions();

    public:
        void Add();
};

#endif
