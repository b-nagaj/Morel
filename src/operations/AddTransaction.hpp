#ifndef ADD_TRANSACTION
#define ADD_TRANSACTION

#include "../utils/Date.hpp"
#include "../entities/Transaction.hpp"
#include "../utils/DBManager.hpp"

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
        bool confirmed; // flag for when a user has confirmed the operation

    // methods
    private:  
        void GetNewTransactions();
        bool ValidateNewTransactionAmount(std::string uncheckedTransactionAmount);
        bool ValidateNewTransactionCategory(std::string uncheckedTransactionCategory);
        bool ConfirmOperation();
        void DisplayNewTransactions();
        void AddNewTransactions();

    public:
        void Add();
};

#endif
