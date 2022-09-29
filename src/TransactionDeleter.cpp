#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "../lib/TransactionDeleter.hpp"

TransactionDeleter::TransactionDeleter() {

    month = "";
    transaction = "";
    numUnwantedTransactions = 0;
    expense = "";

    for (int i = 0; i < MAX_TRANSACTIONS; i++) {
        unwantedTransactions[i] = "";
    }

    dataFilesPath = "";
    dataFilename = "";

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
        dataFilename = dataFilesPath + month + "_" + expense + ".txt";
        //DisplayTransactions();
        GetExistingTransactions();
        numTransactions = (numTransactions + 1);

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

    Clear();

}

void TransactionDeleter::GetUnwantedTransactions() {

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

// void TransactionDeleter::DisplayTransactions() {

//     std::cout << "\nTransactions for (" << expense << ")\n";

//     for (int i = 0; i < numTransactions; i++) {
//         std::cout << "\n" << transactions[i];
//     }

// }

int TransactionDeleter::RemoveTransaction() {

    int i;

    for (i = 0; i < numTransactions; i++) {
        if (transactions[i] == transaction) {
            break;
        }
    }
        
    if (i < numTransactions && transaction != "end") {
        numTransactions = (numTransactions - 1);
        for (int j = i; j < numTransactions; j++) {
            transactions[j] = transactions[j+1];
        }
    }
    else {
        std::cout << "\nERROR: There are no " << expense << " transactions for $" << transaction << "\n"; 
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