#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <boost/filesystem.hpp>

#include "../lib/ReportGenerator.hpp"
#include "../lib/Dialog.hpp"

ReportGenerator::ReportGenerator() {
    
    for (int i = 0; i < sizeof(expenses) / sizeof(expenses[i]); i++) {
        expenses[i] = "";
    }

    reportFilename = "";

    for (int i = 0; i < sizeof(expenseValues)/sizeof(expenseValues[0]); i++) {
        expenseValues[i] = 0;
    }

    expense = "";
    expenseValue = 0;
    dataFilename = "";

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
        numExpenses = 0;

        std::cout << "\n\nGenerated" << std::setw(20) << " ✅" << "\n\n<><><><><><><><><><><><><><>";
    }
    else {
        std::cout << "\n\nGenerated" << std::setw(20) << " ❌" << "\n\n<><><><><><><><><><><><><><>";
    }
    
    Clear();

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
        expense = expenses[i];
        expenseValue = expenseValues[i];
        expenseValues[i] = CalculateExpense();
    } 

}

double ReportGenerator::CalculateExpense() {

    double expenseTotal = expenseValue;
    dataFilename = dataFilesPath + month + "_" + expense + ".txt"; 

    std::ifstream inputFile;
    inputFile.open(dataFilename);
    if (!inputFile) {
        std::cout << "\n" << expense << std::setw(29 - expense.length()) << " ❌";
    }
    else {

        int index = 0;
        while (!inputFile.eof()) {
            std::getline(inputFile, transactions[index]);
            expenseTotal += std::stod(transactions[index]);
            index += 1;
        }

        inputFile.close();

        std::cout << "\n" << expense << std::setw(29 - expense.length()) << " ✅";
    }

    return expenseTotal;

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
