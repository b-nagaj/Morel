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
        Transaction transaction;
        std::string transactionAmount;
        MYSQL_RES * result;

    //methods
    private:
        void GetTransaction();
        bool FindTransaction();
        bool ConfirmOperation();
        void DisplayTransaction();
        void DeleteTheTransaction();

    public:
        void Delete();
};

#endif