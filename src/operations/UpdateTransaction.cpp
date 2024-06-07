#include "UpdateTransaction.hpp"

/**
 * initializes class attributes
*/
UpdateTransaction::UpdateTransaction() {
    numTransactions = 0;
    transactionAmount = "";
    result = nullptr;
}

/**
 * handles invoking the appropriate functions to retrieve a transaction amount
 * to search for, search the database for it, display found transactions to the 
 * console, and update them
*/
void UpdateTransaction::Update() {
    GetTransactions();
    if (FindTransactions()) {
        DisplayTransactions();
        UpdateTheTransactions();
    }
}

/**
 * accepts user input for a transaction's amount
*/
void UpdateTransaction::GetTransactions() {
    std::cout << "\nPlease enter the amount for a transaction you'd like to update\n\n";
    std::cout << "Transaction Amount: ";
    std::getline(std::cin, transactionAmount);
}

/**
 * invokes the GetTransactionsByAmount() from DBManager to search the list of
 * transactions based on the user provided transaction amount
 * 
 * @return true or false based on if a transaction was found
*/
bool UpdateTransaction::FindTransactions() {
    return dbManager.GetTransactionsByAmount(transactionAmount);
}

/**
 * displays each transaction that matches the user provided transaction amount,
 * then prompts the user by invoking ConfirmOperation() for each transaction found
*/
void UpdateTransaction::DisplayTransactions() {
    transactions = dbManager.StoreFoundTransactions(dbManager.stmt, dbManager.result);

    // Display matching transactions
    for (int i = 0; i < dbManager.GetnumRowsReturned(); i++) {
        std::cout << "\nDate: " << transactions[i].GetDate();
        std::cout << "\nAmount: $" << transactions[i].GetAmount();
        std::cout << "\nCategory: " << transactions[i].GetCategory();
        std::cout << std::endl;

        // store the transactionID of each transaction
        std::string transactionID = std::to_string(transactions[i].GetTransactionID());

        // add the current transaction's ID to the list of transactionIDs
        if (ConfirmOperation()) {
            transactionIDs[numTransactions] = transactionID;
            numTransactions++;
        }
    }
}

/**
 * confirms whether the user would like to update the transaction
 * 
 * @return boolean value that represent's the user's input (yes or no)
 */
bool UpdateTransaction::ConfirmOperation() {
    std::string confirmationResponse = "";

    std::cout << "\nUpdate the above transaction? (Y/N): ";
    std::getline(std::cin, confirmationResponse);

    if (confirmationResponse == "Y" || confirmationResponse == "y" ) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * prompts the user to enter new information about a transaction they'd like to update  
 */
void UpdateTransaction::GetNewTransactionInformation() {
    std::string uncheckedTransactionAmount;
    std::string uncheckedTransactionCategory;
    updatedTransactionAmount = 0;
    updatedTransactionCategory = 0;

    std::cout << "\nAmount: ";
    std::getline(std::cin, uncheckedTransactionAmount);

    std::cout << "Category: ";
    std::getline(std::cin, uncheckedTransactionCategory);
    std::cout << "\n";
}

/**
 * updates the transaction or list of transactions the user has agreed to update
 * by invoking the ? DBManager function
*/
void UpdateTransaction::UpdateTheTransactions() {
    int numTransactionsUpdated = 0;
}
