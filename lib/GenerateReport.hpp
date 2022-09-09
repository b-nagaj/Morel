#ifndef GENERATE_REPORT_HPP
#define GENERATE_REPORT_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include "Dialog.hpp"

class GenerateReport : public Helper {

    public: 

        Dialog generateReportDialog;
        std::string lines [50];
        double expenseValues [20];
        std::string expenseNames [20];
        std::string expenseName;
        std::string reportFilename;
        std::string expenseFilename;

        GenerateReport();
        void Generate();
        void Prompt();
        bool ValidateMonth();
        void Calculate();
        void GetPath();
        void GetExpenses();
        double CalculateExpense(double expenseType, std::string name);
        void ClearLinesArray();
        void Report();
        void DisplayExpenses();
        double GetTotal();
        void ClearExpenseArrays();

};

#endif