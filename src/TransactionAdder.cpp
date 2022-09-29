#include <iostream>
#include <iomanip>
#include <fstream>
#include <fstream>
#include <algorithm>

#include "../lib/TransactionAdder.hpp"

TransactionAdder::TransactionAdder() {

    month = "";
    expense = "";
    transaction = "";
    numNewTransactions = 0;

    for (int i = 0; i < MAX_TRANSACTIONS; i++) {
        newTransactions[i] = "";
    }

    dataFilesPath = "";
    dataFilename = "";

}

void TransactionAdder::Add() {

    std::cout << "\nAdd a Transaction";

    GetMonth();
    GetExpenseName();
    GetNewTransactions();
    GetPaths();

    std::string prompt = "\nAdd (" + std::to_string(numNewTransactions) + ") new transactions for the month of " + month + "?" + "(Y/N): ";
    if (Confirm(prompt)) {
        Write();
        std::cout << "\nAdded" << std::setw(23) << " ✅" << "\n\n<><><><><><><><><><><><><><>";
    }
    else {
        std::cout << "\nAdded" << std::setw(23) << " ❌" << "\n\n<><><><><><><><><><><><><><>";
    }

    Clear();

}

void TransactionAdder::GetNewTransactions() {
    
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

    dataFilename = dataFilesPath + month + "_" + expense + ".txt";
    GetExistingTransactions();
    
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