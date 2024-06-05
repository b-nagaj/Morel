#ifndef DELETE_TRANSACTION
#define DELETE_TRANSACTION

#include "../entities/Transaction.hpp"
#include "../utils/DBManager.hpp"

#include <string>
#include <iostream>

class DeleteTransaction {
    // attributes
    private:
        int numTransactions;
        std::string transactionAmount;
        Transaction * transactions;
        std::string transactionIDs [50];
        MYSQL_RES * result;
        DBManager dbManager;
        
    //methods
    private:
        void GetTransaction();
        bool FindTransaction();
        void DisplayTransaction();
        bool ConfirmOperation();
        void DeleteTheTransaction();

    public:
        DeleteTransaction();
        void Delete();
};

#endif
