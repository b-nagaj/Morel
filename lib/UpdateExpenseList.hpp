#ifndef UPDATE_EXPENSE_LIST_HPP
#define UPDATE_EXPENSE_LIST_HPP

#include <fstream>
#include <string>

#include "Helper.hpp"

class UpdateExpenseList : public Helper {

    public:

        std::string lines [23];
        
        UpdateExpenseList();
        void Update();
        void Prompt();
        void Write();
        
};

#endif