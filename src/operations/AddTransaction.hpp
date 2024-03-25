#ifndef ADD_TRANSACTION
#define ADD_TRANSACTION

#include "../utils/Date.hpp"
#include "../entities/Transaction.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <mysql/mysql.h>
#include <cctype>
#include <map>

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
        bool ConfirmOperation();
        void AddNewTransactions();

    public:
        void Add();
};

#endif
