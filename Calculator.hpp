#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#pragma once

class Calculator {

public: 

    std::string month;
    std::string reportFilename;
    std::ofstream outputFile;
    std::string expenseName;
    std::string lines [50];
    double expenses [9];
    std::string expenseNames [9] = { "Groceries",
                                     "Eating_Out",
                                     "Gas",
                                     "Rent",
                                     "Electricity",
                                     "Internet",
                                     "Water",
                                     "Car",
                                     "Venmo" };

    Calculator();
    void Prompt();
    void ClearArray();
    double CalculateExpense(double expenseType, std::string name);
    void Report();
    void Calculate();
    void Banner(std::ostream& stream);
    std::string SetExpenseFilename(std::string expenseFilename);
    void DisplayExpenses();
    double GetTotal();

};