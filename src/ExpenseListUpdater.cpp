#include <iostream>
#include <fstream>
#include <iomanip>

#include "../lib/ExpenseListUpdater.hpp"

ExpenseListUpdater::ExpenseListUpdater() {

    for (int i = 0; i < (sizeof(lines) / sizeof(lines[i])); i++) {
        lines[i] = "";
    }
    for (int i = 0; i < (sizeof(expenses) / sizeof(expenses[0])); i++) {
        expenses[i] = "";
    }

    expense = "";
    numExpenses = 0;
    username = "";
    dataFilesPath = "";
    reportFilesPath = "";

}

void ExpenseListUpdater::Update() {

    std::cout << "\nUpdate Expense List";

    GetNewExpenses();

    std::cout << "\nUpdate your list of expenses?(Y/N): ";
    std::string yesNo;
    std::cin >> yesNo;

    if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes") {
        GetUsername();
        GetPaths();
        Write();

        std::cout << "\nUpdated" << std::setw(22) << " ✅" << "\n\n<><><><><><><><><><><><><><>";
    }
    else {
        std::cout << "\nUpdated" << std::setw(22) << " ❌" << "\n\n<><><><><><><><><><><><><><>";
    }   

}

void ExpenseListUpdater::GetNewExpenses() {

    std::cout << "\n\nPlease give a list of up to 20 expenses"
              << "\nInclude each expense on a seperate line"
              << "\nType 'end' to indicate the end of the list\n\n";

    numExpenses = -1;
    while (expense != "end") {
        numExpenses++;
        std::cout << "Expense" << "[" << (numExpenses + 1) << "]: ";
        std::cin >> expense;
        expenses[numExpenses] = expense;
    }
    //numExpenses--;

}

void ExpenseListUpdater::Write() {

    outputFile.open("config.txt");

    if (outputFile) {
        outputFile << username << std::endl;
        outputFile << dataFilesPath << std::endl;
        outputFile << reportFilesPath << std::endl;

        for (int i = 0; i < numExpenses; i++) {
            outputFile << expenses[i] << std::endl;
        }
    }

    outputFile.close();

}