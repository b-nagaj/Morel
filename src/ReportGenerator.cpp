#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <boost/filesystem.hpp>

#include "../lib/ReportGenerator.hpp"
#include "../lib/Dialog.hpp"

ReportGenerator::ReportGenerator() {

    numExpenses = 0;

    for (int i = 0; i < sizeof(expenseValues)/sizeof(expenseValues[0]); i++) {
        expenseValues[i] = 0;
    }

    for (int i = 0; i < sizeof(expenses) / sizeof(expenses[i]); i++) {
        expenses[i] = "";
    }

}

void ReportGenerator::Generate() {

    std::cout << "\nGenerate A Report";

    GetMonth();
    GetPaths();
    GetExpenses();

    std::cout << "\nMake an expense report for " << month << "?" << "(Y/N) ";
    std::string yesNo;
    std:: cin >> yesNo;

    if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes"){
        Calculate();
        Report();
        inputFile.close();
        outputFile.close(); 
        ClearExpenseArrays();
        numExpenses = 0;

        std::cout << "\n\nGenerated" << std::setw(20) << " ✅" << "\n\n<><><><><><><><><><><><><><>";
    }
    else {
        std::cout << "\n\nGenerated" << std::setw(20) << " ❌" << "\n\n<><><><><><><><><><><><><><>";
    }

}

void ReportGenerator::GetMonth() {

    std::cout << "\n\nMonth: ";
    std::cin >> month;

    if (!ValidateMonth()) {
        GetMonth();
    }

}

void ReportGenerator::Calculate() {

    reportFilename = reportFilesPath + month + "_Report.txt";
    outputFile.open(reportFilename);

    for (int i = 0; i < numExpenses; i++) {
        expenseValues[i] = CalculateExpense(expenseValues[i], expenses[i]);
    } 

}

double ReportGenerator::CalculateExpense(double expenseType, std::string expenseName) {

    expenseFilename = dataFilesPath + month + "_" + expenseName + ".txt"; 

    std::ifstream inputFile;
    inputFile.open(expenseFilename);
    if (!inputFile) {
        std::cout << "\n" << expenseName << std::setw(29 - expenseName.length()) << " ❌";
    }
    else {
        ClearLinesArray();

        int index = 0;
        while (!inputFile.eof()) {
            std::getline(inputFile, lines[index]);
            expenseType += std::stod(lines[index]);
            index += 1;
        }

        inputFile.close();
        std::cout << "\n" << expenseName << std::setw(29 - expenseName.length()) << " ✅";
    }

    return expenseType;

}

void ReportGenerator::ClearLinesArray() {

    for (int i = 0; i < 20; i++) {
        lines[i] = "";
    }

}

void ReportGenerator::Report() {

    reportGeneratorDialog.ReportBanner(outputFile);
    outputFile << "\n";
    DisplayExpenses();
    outputFile << "\n\n\tTotal:" << std::setw(17) << "$" << std::fixed << std::setprecision(2) << GetTotal() << "\n";

}

void ReportGenerator::DisplayExpenses() {

    for (int i = 0; i < numExpenses; i++) {
        outputFile << "\n\t" << expenses[i] << std::setw(23 - expenses[i].length()); 
        outputFile << std::fixed << std::setprecision(2) << "$" << expenseValues[i];
    }

}

double ReportGenerator::GetTotal() {

    double total;

    for (int i = 0; i < sizeof(expenseValues)/sizeof(expenseValues[0]); i++) {
        total += expenseValues[i]; 
    }

    return total;

}

void ReportGenerator::ClearExpenseArrays() {

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        expenseValues[i] = 0;
    }

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        expenses[i] = "";
    }

}
