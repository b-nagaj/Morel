#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "../lib/TransactionDeleter.hpp"

TransactionDeleter::TransactionDeleter() {

    for (int i = 0; i < MAX_TRANSACTIONS; i++) {
        unwantedTransactions[i] = "";
    }

    month = "";
    dataFilesPath = "";
    dataFilename = "";
    transaction = "";
    numUnwantedTransactions = 0;
    expenseName = "";

}

void TransactionDeleter::Delete() {

    std::cout << "\nDelete a Transaction";

    GetMonth();
    GetExpenseName();
    GetUnwantedTransactions();
    GetPaths();

    std::cout << "\nDelete (" << numUnwantedTransactions << ") existing transaction for the month of " << month << "?" << "(Y/N) "; 
    std::string yesNo;
    std:: cin >> yesNo;

    if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes"){
        dataFilename = dataFilesPath + month + "_" + expenseName + ".txt";
        GetExistingTransactions(dataFilename);
        numTransactions = (numTransactions + 1);

        DisplayTransactions();

        for (int i = 0; i <= numUnwantedTransactions && unwantedTransactions[i] != "end"; i++) {
            transaction = unwantedTransactions[i];
            numTransactions = RemoveTransaction();
        }

        Write();
        std::cout << "\nDeleted" << std::setw(21) << " ✅" << "\n\n<><><><><><><><><><><><><><>";
    }
    else {
        std::cout << "\nDeleted" << std::setw(21) << " ❌" << "\n\n<><><><><><><><><><><><><><>";
    }

}

void TransactionDeleter::GetMonth() {

    std::cout << "\n\nMonth: ";
    std::cin >> month;

    if (!ValidateMonth()) {
        month = "";
        GetMonth();
    }

}

void TransactionDeleter::GetExpenseName() {

    std::cout << "Expense Type: ";
    std::cin >> expenseName;

    if (!ValidateExpenseName()) {
        expenseName = "";
        GetExpenseName();
    }

}

bool TransactionDeleter::ValidateExpenseName() {

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

void TransactionDeleter::GetUnwantedTransactions() {

    transaction = "";
    numUnwantedTransactions = 0;

    std::cout << "\nTransactions to be deleted (type 'end' to indicate the end of the list): \n\n";

    numUnwantedTransactions = -1;
    while (transaction != "end") {
        numUnwantedTransactions++;
        std::cout << "Transaction" << "[" << (numUnwantedTransactions + 1) << "] Amount: ";
        std::cin >> transaction;

        if (transaction != "end" && !ValidateUnwantedTransactions()) {
            numUnwantedTransactions--;
        }
        else {
            unwantedTransactions[numUnwantedTransactions] = transaction;
        }
    }
    transaction = ""; 

}

bool TransactionDeleter::ValidateUnwantedTransactions() {

    bool isValid = true;
    
    std::string transactionWithoutDecimal = transaction;
    transactionWithoutDecimal.erase(remove(transactionWithoutDecimal.begin(), transactionWithoutDecimal.end(), '.'), transactionWithoutDecimal.end());
    
    if (std::all_of(transactionWithoutDecimal.begin(), transactionWithoutDecimal.end(), ::isdigit) == false) {
        std::cout << "\nERROR: The transaction you entered is not a numerical value\n\n";
        isValid = false;
    }
    
    return isValid;

}

void TransactionDeleter::DisplayTransactions() {

    std::cout << "\nTransactions for " << expenseName;

    for (int i = 0; i < numTransactions; i++) {
        std::cout << "\n" << transactions[i];
    }

}

int TransactionDeleter::RemoveTransaction() {

    int i;

    for (i = 0; i < numTransactions; i++)
        if (transactions[i] == transaction)
            break;
    
    // If x found in array
    if (i < numTransactions && transaction != "end")
    {
        // reduce size of array and move all
        // elements on space ahead
        numTransactions = (numTransactions - 1);
        for (int j = i; j < numTransactions; j++)
            transactions[j] = transactions[j+1];
    }
    else {
        std::cout << "\nERROR: There are no " << expenseName << " transactions for $" << transaction << "\n"; 
    }
    
    return numTransactions;

}

void TransactionDeleter::Write() {

    outputFile.open(dataFilename);

    for (int i = 0; i < numTransactions; i++) {
        if (i == 0) {
            outputFile << transactions[i];
        }
        else {
            outputFile << "\n" << transactions[i];
        }
    }

    outputFile.close();

}