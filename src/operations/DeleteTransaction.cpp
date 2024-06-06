#include "DeleteTransaction.hpp"

/**
 * initializes class attributes
*/
DeleteTransaction::DeleteTransaction() {
    numTransactions = 0;
    transactionAmount = "";
    result = nullptr;
}

/**
 * handles invoking the appropriate functions to retrieve a transaction amount
 * to search for, search the database for it, display found transactions to the 
 * console, and delete it
*/
void DeleteTransaction::Delete() {
    GetTransactions();
    if (FindTransactions()) {
        DisplayTransactions();
        DeleteTheTransactions();
    }
}

/**
 * accepts user input for a transaction's amount
*/
void DeleteTransaction::GetTransactions() {
    std::cout << "\nPlease enter the amount for a transaction you'd like to delete\n\n";
    std::cout << "Transaction Amount: ";
    std::getline(std::cin, transactionAmount);
}

/**
 * invokes the GetTransactionsByAmount() from DBManager to search the list of
 * transactions based on the user provided transaction amount
 * 
 * @return true or false based on if a transaction was found
*/
bool DeleteTransaction::FindTransactions() {
    return dbManager.GetTransactionsByAmount(transactionAmount);
}

/**
 * displays each transaction that matches the user provided transaction amount,
 * then prompts the user by invoking ConfirmOperation() for each transaction found
*/
void DeleteTransaction::DisplayTransactions() {
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
 * confirms whether the user would like to delete the transaction
 * 
 * @return boolean value that represent's the user's input (yes or no)
 */
bool DeleteTransaction::ConfirmOperation() {
    std::string confirmationResponse = "";

    std::cout << "\nDelete the above transaction? (Y/N): ";
    std::getline(std::cin, confirmationResponse);

    if (confirmationResponse == "Y" || confirmationResponse == "y" ) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Deletes the transaction or list of transactions the user has agreed to delete
 * by invoking the DeleteTransaction() DBManager function
*/
void DeleteTransaction::DeleteTheTransactions() {
    int numTransactionsDeleted = 0;

    // delete each transaction the user has chosen to delete
    for (int i = 0; i < numTransactions; i++) {
        if (dbManager.DeleteTransactions(transactionIDs[i])) {
            numTransactionsDeleted++;
        }
    }
    std::cout << "\n" << numTransactionsDeleted << " transaction(s) deleted ✅";
}
