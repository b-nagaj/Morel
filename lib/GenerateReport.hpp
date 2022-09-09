#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include "../lib/Dialog.hpp"

#pragma once

class GenerateReport {

public: 

    Dialog generateReportDialog;
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
    std::string lines [50];
    double expenses [20];
    std::string expenseNames[20];
    std::string expenseName;
    int numExpenses;
    std::string month;
    std::string dataFilesPath;
    std::string reportFilesPath;
    std::string reportFilename;
    std::string expenseFilename;
    std::ifstream inputFile;
    std::ofstream outputFile;

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