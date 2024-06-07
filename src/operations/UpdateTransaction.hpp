#ifndef UPDATE_TRANSACTION
#define UPDATE_TRANSACTION

#include <iostream>
#include <string>

#include "../entities/Transaction.hpp"
#include "../utils/DBManager.hpp"

class UpdateTransaction {
    // attributes
        private:
            int numTransactions;
            int updatedTransactionAmount;
            int updatedTransactionCategory;
            std::string transactionAmount;
            Transaction * transactions;
            std::string transactionIDs [50];
            MYSQL_RES * result;
            DBManager dbManager;

    // methods
        private:
            void GetTransactions();
            bool FindTransactions();
            void DisplayTransactions();
            bool ConfirmOperation();
            void GetNewTransactionInformation();
            void UpdateTheTransactions();

        public:
            UpdateTransaction();
            void Update();
};

#endif 
