#include <fstream>
#include <string>

#include "../lib/GenerateReport.hpp"

#pragma once

class UpdateExpenseList {

    public:

        std::ofstream outputFile;
        std::string expense;
        std::string expenses[20];
        int expenseListSize;
        
        UpdateExpenseList();
        void Update();
        void Prompt();
        void Write();
        
};