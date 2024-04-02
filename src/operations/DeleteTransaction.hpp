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
        std::string transactionIDs [50];
        MYSQL_RES * result;

    //methods
    private:
        void GetTransaction();
        bool FindTransaction();
        bool ConfirmOperation();
        void DisplayTransaction();
        void DeleteTheTransaction();

    public:
        DeleteTransaction();
        void Delete();
};

#endif