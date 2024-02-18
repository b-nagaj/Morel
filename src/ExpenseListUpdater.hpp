#ifndef EXPENSE_LIST_UPDATER_HPP
#define EXPENSE_LIST_UPDATER_HPP

#include <fstream>
#include <string>

#include "utils/Helper.hpp"

class ExpenseListUpdater : public Helper {

    public:

        std::string lines [23];
        
    public:
    
        ExpenseListUpdater();
        void Update();
        void GetNewExpenses();
        void Write();
        
};

#endif