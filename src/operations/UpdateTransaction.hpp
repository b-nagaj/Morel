#ifndef UPDATE_TRANSACTION
#define UPDATE_TRANSACTION

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

#include "../entities/Transaction.hpp"
#include "../utils/DBManager.hpp"
#include "../utils/Date.hpp"

class UpdateTransaction {
    // attributes
        private:
            int numTransactions;
            std::string updatedTransactionAmount;
            std::string updatedTransactionCategory;
            std::string transactionAmount;
            Transaction * foundTransactions;
            Transaction transactions [50];
            MYSQL_RES * result;
            DBManager dbManager;

    // methods
        private:
            void GetTransactions();
            bool FindTransactions();
            void DisplayTransactions();
            bool ConfirmOperation();
            void GetNewTransactionInformation(int index);
            bool ValidateNewTransactionAmount(std::string uncheckedTransactionAmount);
            bool ValidateNewTransactionCategory(std::string uncheckedTransactionCategory);
            void UpdateTheTransactions();

        public:
            UpdateTransaction();
            void Update();
};

#endif 
