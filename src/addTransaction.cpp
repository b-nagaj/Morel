#include <iostream>
#include <iomanip>
#include <fstream>
#include <fstream>
#include <algorithm>

#include "../lib/addTransaction.hpp"

AddTransaction::AddTransaction() {

    for (int i = 0; i < MAX_TRANSACTIONS; i++) {
        newTransactions[i] = "";
    }

    month = "";
    dataFilesPath = "";
    dataFilename = "";
    transaction = "";
    numNewTransactions = 0;

}

void AddTransaction::Add() {

    std::cout << "\nAdd a Transaction";

    Prompt();
    GetPaths();

    std::cout << "Add (" << numNewTransactions << ") new transactions for the month of " << month << "?" << "(Y/N) "; 
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

void AddTransaction::Prompt() {

    std::cout << "\n\nMonth: ";
    std::cin >> month;

    std::cout << "Expense Type: ";
    std::cin >> expense;

    std::cout << "\nNew Transactions: \n\n";

    numNewTransactions = 0;
    while (transaction != "end") {
        std::cout << "Transaction" << "[" << (numNewTransactions + 1) << "] Amount: ";
        std::cin >> transaction;
        std::cout << "\n";
        newTransactions[numNewTransactions] = transaction;
        numNewTransactions++;
    }

    if (!ValidateMonth()) {
        Prompt();
    }
    else {
        numNewTransactions--;
        transaction = "";
    }

}

// bool AddTransaction::ValidateExpense() {

//     bool validExpense = false;

//     GetExpenses();

//     for (int i = 0; i < numExpenses; i++) {
//         if (expenses[i] == expense) {
//             validExpense = true;
//             break;
//         }
//     }

//     if (!validExpense) {
//         std::cout << "\nERROR: The expense you entered is not listed in your expense list\n\nGenerated ❌\n\n<><><><><><><><><><><><><><>";
//     }

//     return validExpense;

// }

// bool AddTransaction::ValidateTransaction() {

//     bool isValid;

//     if (std::all_of(month.begin(), month.end(), ::isdigit) == false) {
//         std::cout << "\nERROR: The value(s) you entered is not an integer\n\n<><><><><><><><><><><><><><>";
//         isValid = false;
//     }

//     return isValid;

// }

void AddTransaction::Write() {

    dataFilename = dataFilesPath + month + "_" + expense + ".txt";
    GetTransactions(dataFilename);
    
    if (numTransactions + numNewTransactions >= MAX_TRANSACTIONS) {
        std::cout << "\nError: you've reached the maximum amount of transactions\n\n<><><><><><><><><><><><><><>";
    }
    else {
        for (int i = 0; i < numNewTransactions; i++) {
            transactions[numTransactions + 1] = newTransactions[i];
            numTransactions++;
        }

        outputFile.open(dataFilename);

        if (outputFile) {
            for (int i = 0; i < numTransactions + 1; i++) {
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