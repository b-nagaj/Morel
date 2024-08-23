#ifndef VIEW_TRANSACTION
#define VIEW_TRANSACTION

#include "../entities/Transaction.hpp"
#include "../utils/DBManager.hpp"

#include <string>
#include <iostream>

class ViewTransaction {
    // attributes
    private:
        std::string lesserDate;
        std::string greaterDate;
        Transaction * transactions; 
        MYSQL_RES * result;
        DBManager dbManager;

    // methods
    private:
        bool GetDateRange();
        bool ConfirmOperation();
        bool FindTransactions();
        void DisplayTransactions();

    public:
        ViewTransaction();
        void View();
};

#endif
