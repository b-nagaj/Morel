#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>

#include "Calculator.hpp"
#include "Dialog.hpp"

Calculator::Calculator() {

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        expenses[i] = 0;
    }

}

void Calculator::Prompt() {

    std::cout << " __  __                _" 
              << "\n|  \\/  | ___  _ __ ___| |"
              << "\n| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n| |  | | (_) | | |  __/ |"
              << "\n|_|  |_|\\___/|_|  \\___|_|";

    Dialog myDialog;
    std::string choice;
    int option;

    while (option != 6) {
        option = myDialog.Menu();

        switch (option) {
        case 1 :
            std::cout << "\nGenerate A Report";
            std::cout << "\n\nMonth: ";
            std::cin >> month;

            std::cout << "\nMake an expense report for " << month << "?" << "(Y/N) ";
            std:: cin >> choice;

            if (choice == "Y" || choice == "Yes" || choice == "y" || choice == "yes"){
                Calculate();
            }
            else {
                myDialog.Menu();
            }
        
            break;

        case 2 : 
            std::cout << "\nView A Report";
            break;
        
        case 3 :
            std::cout << "\nUpdate A Report";
            break;
        
        case 4 :
            std::cout << "\nUpdate An Expense";
            break;
        
        case 5 :
            std::cout << "\nHelp";
            break;
        
        case 6 :
            std::cout << "\nQuitting!\n\n";
            break;
        }
    }

}

void Calculator::ClearArray() {

    for (int i = 0; i < 20; i++) {
        lines[i] = "";
    }

}

double Calculator::CalculateExpense(double expenseType, std::string expenseName) {

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

void Calculator::Report() {

    Banner(outputFile);
    outputFile << "\n";
    DisplayExpenses();
    outputFile << "\n\n\tTotal:" << std::setw(17) << "$" << std::fixed << std::setprecision(2) << GetTotal() << "\n";

}

void Calculator::Calculate() {

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

void Calculator::Banner(std::ostream& stream) {

    stream << " \t __  __                _" 
              << "\n\t|  \\/  | ___  _ __ ___| |"
              << "\n\t| |\\/| |/ _ \\| '__/ _ \\ |"
              << "\n\t| |  | | (_) | | |  __/ |"
              << "\n\t|_|  |_|\\___/|_|  \\___|_|";
    
}

std::string Calculator::SetExpenseFilename(std::string expenseName) {

    std::string expenseFilename = "/home/bryce/Documents/Monthly_Expenses/Data/" + month + "_2022/" + month + "_2022_" + expenseName + ".txt";
    return expenseFilename;

}

void Calculator::DisplayExpenses() {

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        outputFile << "\n\t" << expenseNames[i] << std::setw(23 - expenseNames[i].length()); 
        outputFile << std::fixed << std::setprecision(2) << "$" << expenses[i];
    }

}

double Calculator::GetTotal() {

    double total;

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        total += expenses[i]; 
    }

    return total;

}