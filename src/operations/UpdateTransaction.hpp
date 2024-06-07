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
            bool UpdateTheTransaction();

        public:
            UpdateTransaction();
            void Update();
};

#endif 
