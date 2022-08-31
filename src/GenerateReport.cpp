#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>

#include "../lib/GenerateReport.hpp"
#include "../lib/Dialog.hpp"

GenerateReport::GenerateReport() {

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        expenses[i] = 0;
    }

}

void GenerateReport::Prompt() {

    std::cout << "\nGenerate A Report";
    std::cout << "\n\nMonth: ";
    std::cin >> month;

}

void GenerateReport::Generate() {

    Dialog myDialog;

    Prompt();

    bool validMonth = false;
    for (int i = 0; i < 24; i++) {
        if (validMonths[i] == month) {
            validMonth = true;
            break;
        }
    }

    if (validMonth) {
        std::cout << "\nMake an expense report for " << month << "?" << "(Y/N) ";
        std::string yesNo;
        std:: cin >> yesNo;

        if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes"){
            SetMonth(month);
            Calculate();
        }
        else {
            myDialog.Menu();
        }
    }
    else {
        myDialog.errorMessage = "\nERROR: The value you entered is not a real month";
        std::cout << myDialog.errorMessage;
    }

    myDialog.option = 0;

}

void GenerateReport::ClearArray() {

    for (int i = 0; i < 20; i++) {
        lines[i] = "";
    }

}

double GenerateReport::CalculateExpense(double expenseType, std::string expenseName) {

    std::string expenseFilename = SetExpenseFilename(expenseName);

    std::ifstream inputFile;
    inputFile.open(expenseFilename);
    if (!inputFile) {
        std::cout << "\n" << expenseName << std::setw(27 - expenseName.length()) << " ❌";
    }
    else {
        ClearArray();

        int index = 0;
        while (!inputFile.eof()) {
            std::getline(inputFile, lines[index]);
            expenseType += std::stod(lines[index]);
            index += 1;
        }

        inputFile.close();
        std::cout << "\n" << expenseName << std::setw(27 - expenseName.length()) << " ✅";
    }

    return expenseType;

}

void GenerateReport::Report() {

    Dialog newDialog;
    newDialog.ReportBanner(outputFile);
    outputFile << "\n";
    DisplayExpenses();
    outputFile << "\n\n\tTotal:" << std::setw(17) << "$" << std::fixed << std::setprecision(2) << GetTotal() << "\n";

}

void GenerateReport::Calculate() {

    reportFilename = "/home/bryce/Documents/Monthly_Expenses/Reports/" + month + "_2022_Report.txt";
    outputFile.open(reportFilename);

    std::cout << "\nCreating expense report...\n";
    
    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        expenses[i] = CalculateExpense(expenses[i], expenseNames[i]);
    }

    Report();

    std::cout << "\n\nDone!\n\n"
              << "<><><><><><><><><><><><><><>"; 
    outputFile.close();

}

std::string GenerateReport::SetExpenseFilename(std::string expenseName) {

    std::string expenseFilename = "/home/bryce/Documents/Monthly_Expenses/Data/" + month + "_2022/" + month + "_2022_" + expenseName + ".txt";
    return expenseFilename;

}

void GenerateReport::DisplayExpenses() {

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        outputFile << "\n\t" << expenseNames[i] << std::setw(23 - expenseNames[i].length()); 
        outputFile << std::fixed << std::setprecision(2) << "$" << expenses[i];
    }

}

double GenerateReport::GetTotal() {

    double total;

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        total += expenses[i]; 
    }

    return total;

}

void GenerateReport::SetMonth(std::string m) {

    month = m;

}