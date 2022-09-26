#ifndef REPORT_GENERATOR_HPP
#define REPORT_GENERATOR_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include "Dialog.hpp"

class ReportGenerator : public Helper {

    public: 

        Dialog reportGeneratorDialog;
        std::string lines [50];
        std::string expenseName;
        std::string reportFilename;
        std::string expenseFilename;

        ReportGenerator();
        void Generate();
        void GetMonth();
        void Calculate();
        double CalculateExpense(double expenseType, std::string name);
        void ClearLinesArray();
        void Report();
        void DisplayExpenses();
        double GetTotal();
        void ClearExpenseArrays();

};

#endif