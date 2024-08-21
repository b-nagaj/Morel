#ifndef VIEW_TRANSACTION
#define VIEW_TRANSACTION

#include "../entities/Transaction.hpp"

#include <string>

class ViewTransaction {
    // attributes
    private:
        std::string lesserDate;
        std::string greaterDate;
        Transaction transactions[50];

    // methods
    private:
        void GetDateRange();
        void ViewTransactions();
        void DisplayTransactions();

    public:
        ViewTransaction();
        void View();
};

#endif
