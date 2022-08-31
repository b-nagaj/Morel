#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include "../lib/Dialog.hpp"

#pragma once

class GenerateReport {

public: 

    Dialog generateReportDialog;
    std::string month;
    std::string validMonths[24] = { "january",
                                    "January",
                                    "february",
                                    "February",
                                    "march",
                                    "March",
                                    "april",
                                    "April",
                                    "may",
                                    "May",
                                    "june",
                                    "June",
                                    "july",
                                    "July",
                                    "august",
                                    "August",
                                    "september",
                                    "September",
                                    "october",
                                    "October",
                                    "november",
                                    "November",
                                    "december",
                                    "December" };
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

    GenerateReport();
    void Generate();
    void Prompt();
    bool ValidateMonth();
    void SetMonth(std::string m);
    void Calculate();
    double CalculateExpense(double expenseType, std::string name);
    std::string SetExpenseFilename(std::string expenseFilename);
    void ClearArray();
    void Report();
    void DisplayExpenses();
    double GetTotal();

};