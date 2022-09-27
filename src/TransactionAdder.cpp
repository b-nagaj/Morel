#include <iostream>
#include <iomanip>
#include <fstream>
#include <fstream>
#include <algorithm>

#include "../lib/TransactionAdder.hpp"

TransactionAdder::TransactionAdder() {

    for (int i = 0; i < MAX_TRANSACTIONS; i++) {
        newTransactions[i] = "";
    }

    month = "";
    dataFilesPath = "";
    dataFilename = "";
    transaction = "";
    expenseName = "";
    numNewTransactions = 0;

}

void TransactionAdder::Add() {

    std::cout << "\nAdd a Transaction";

    GetMonth();
    GetExpenseName();
    GetNewTransactions();
    GetPaths();

    std::cout << "\nAdd (" << numNewTransactions << ") new transactions for the month of " << month << "?" << "(Y/N) "; 
    std::string yesNo;
    std:: cin >> yesNo;

    if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes"){
        Write();
        std::cout << "\nAdded" << std::setw(23) << " ✅" << "\n\n<><><><><><><><><><><><><><>";
    }
    else {
        std::cout << "\nAdded" << std::setw(23) << " ❌" << "\n\n<><><><><><><><><><><><><><>";
    }

}

void TransactionAdder::GetMonth() {

    std::cout << "\n\nMonth: ";
    std::cin >> month;

    if (!ValidateMonth()) {
        month = "";
        GetMonth();
    }

}

void TransactionAdder::GetExpenseName() {

    std::cout << "Expense Type: ";
    std::cin >> expenseName;

    if (!ValidateExpenseName()) {
        expenseName = "";
        GetExpenseName();
    }

}

bool TransactionAdder::ValidateExpenseName() {

    bool validExpense = false;

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

    return validExpense;

}

void TransactionAdder::GetNewTransactions() {

    transaction = "";
    numNewTransactions = 0;

    std::cout << "\nNew Transactions (type 'end' to indicate the end of the list): \n\n";

    numNewTransactions = -1;
    while (transaction != "end") {
        numNewTransactions++;
        std::cout << "Transaction" << "[" << (numNewTransactions + 1) << "] Amount: ";
        std::cin >> transaction;

        if (transaction != "end" && !ValidateNewTransactions()) {
            numNewTransactions--;
        }
        else {
            newTransactions[numNewTransactions] = transaction;
        }
    }
    transaction = ""; 

}

bool TransactionAdder::ValidateNewTransactions() {

    bool isValid = true;
    
    std::string transactionWithoutDecimal = transaction;
    transactionWithoutDecimal.erase(remove(transactionWithoutDecimal.begin(), transactionWithoutDecimal.end(), '.'), transactionWithoutDecimal.end());
    
    if (std::all_of(transactionWithoutDecimal.begin(), transactionWithoutDecimal.end(), ::isdigit) == false) {
        std::cout << "\nERROR: The transaction you entered is not a numerical value\n\n";
        isValid = false;
    }
    
    return isValid;

}

void TransactionAdder::Write() {

    dataFilename = dataFilesPath + month + "_" + expenseName + ".txt";
    GetExistingTransactions(dataFilename);
    
    if (numTransactions + numNewTransactions >= MAX_TRANSACTIONS) {
        std::cout << "\nError: you've reached the maximum amount of transactions\n";
    }
    else {
        for (int i = 0; i < numNewTransactions; i++) {
            transactions[numTransactions + 1] = newTransactions[i];
            numTransactions++;
        }

        outputFile.open(dataFilename);

        if (outputFile) {
            for (int i = 0; i <= numTransactions ; i++) {
                if (i == 0) {
                    outputFile << transactions[i];
                }
                else {
                    outputFile << "\n" << transactions[i];
                }
            }
        }
        outputFile.close();
    }

}