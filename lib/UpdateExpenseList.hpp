#include <fstream>
#include <string>

#pragma once

class UpdateExpenseList {

    public:

        std::string lines [23];
        std::string expenses [20];
        std::string expense;
        int numExpenses;
        std::string username;
        std::string dataFilesPath;
        std::string reportFilesPath;
        std::ifstream inputFile;
        std::ofstream outputFile;
        
        UpdateExpenseList();
        void Update();
        void Prompt();
        void GetUsername();
        void GetPaths();
        void Write();
        
};