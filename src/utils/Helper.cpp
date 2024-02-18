#include <iostream>

#include "Helper.hpp"

// Expenses

void Helper::GetExpenses() {

    inputFile.open("config.txt");

    for (int i = 0; i < 3; i++) {
        std::getline(inputFile, expense);
    }

    numExpenses = 0;
    if (inputFile) {
        while (expense != "" && numExpenses < MAX_EXPENSE_SIZE) {
            std::getline(inputFile, expense);
            expenses[numExpenses] = expense;
            numExpenses++;
        }
        numExpenses--;
    }

    inputFile.close();

}

// Transactions

void Helper::GetExistingTransactions() {

    inputFile.open(dataFilename);
    
    std::string transaction = "";
    numTransactions = 0;
    if (inputFile) {
        while (std::getline(inputFile, transaction)) {
            transactions[numTransactions] = transaction;
            numTransactions++;
        } 
        numTransactions--;
    }

    inputFile.close();

}

void Helper::GetExpenseName() {

    std::cout << "Expense Name: ";
    std::cin >> expense;

    if (!ValidateExpenseName()) {
        GetExpenseName();
    }

}

// Data

void Helper::GetUsername() {

    inputFile.open("config.txt"); 
    std::getline(inputFile, username);
    inputFile.close();

}

void Helper::GetPaths() {

    std::string paths [3];

    inputFile.open("config.txt");

    int i = 0;
    while (i < 3) {
        std::getline(inputFile, paths[i], '\n');
        i++;
    }

    dataFilesPath = paths[1];
    reportFilesPath = paths[2];

    inputFile.close();

}

// Validation

bool Helper::ValidateMonth() {

    bool validMonth = false;

    for (int i = 0; i < NUM_VALID_MONTHS; i++) {
        if (validMonths[i] == month) {
            validMonth = true;
            break;
        }
    }

    if (validMonth == false) {
        std::cout << "\nERROR: The month you entered is not a real month\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
    }

    return validMonth;

}

bool Helper::ValidateExpenseName() {

    bool validExpense = false;
    std::string expenseName = expense;

    GetExpenses();

    for (int i = 0; i < numExpenses; i++) {
        if (expenses[i] == expenseName) {
            validExpense = true;
            break;
        }
    }

    if (!validExpense) {
        std::cout << "\nERROR: The expense you entered is not listed in your expense list\n\n";
    }

    expense = expenseName;

    return validExpense;

}

// Utilities

void Helper::GetMonth() {

    std::cout << "\n\nMonth: ";
    std::cin >> month;

    if (!ValidateMonth()) {
        month = "";
        GetMonth();
    }

}

void Helper::Clear() {

    for (int i = 0; i < sizeof(expenses)/sizeof(expenses[0]); i++) {
        expenses[i] = "";
    }

    for (int i = 0; i < sizeof(expenseValues)/sizeof(expenseValues[0]); i++) {
        expenseValues[i] = 0;
    }

    for (int i = 0; i < sizeof(transactions)/sizeof(transactions[0]); i++) {
        transactions[i] = "";
    }

}

bool Helper::Confirm(std::string prompt) {

    bool confirmed = false;

    std::string yesOrNo;
    std::cout << prompt;
    std::cin >> yesOrNo;

    if (yesOrNo == "Y" || yesOrNo == "Yes" || yesOrNo == "y" || yesOrNo == "yes") {
        confirmed = true;
    }

    return confirmed;

}