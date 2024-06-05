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
    GetTransaction();
    if (FindTransaction()) {
        DisplayTransaction();
        DeleteTheTransaction();
    }
}

/**
 * accepts user input for a transaction's amount
*/
void DeleteTransaction::GetTransaction() {
    std::cout << "\nPlease enter the amount for a transaction you'd like to delete\n\n";
    std::cout << "Transaction Amount: ";
    std::getline(std::cin, transactionAmount);
}

/**
 * invokes the GetTransactionByAmount DBManager function to search the list of
 * transactions based on the user provided transaction amount
 * 
 * @return true or false based on if a transaction was found
*/
bool DeleteTransaction::FindTransaction() {
    return dbManager.GetTransactionByAmount(transactionAmount);
}

/**
 * displays each transaction that matches the user provided transaction amount,
 * then prompts the user by invoking ConfirmOperation() for each transaction found
*/
void DeleteTransaction::DisplayTransaction() {
    transactions = dbManager.StoreFoundTransaction(dbManager.stmt, dbManager.result);

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
 * asks the user to proceed with deletion of a transaction or list of transactions
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
void DeleteTransaction::DeleteTheTransaction() {
    // delete each transaction the user has chosen to delete
    for (int i = 0; i < numTransactions; i++) {
        dbManager.DeleteTransaction(transactionIDs[i]);
    }
    std::cout << "\n" << numTransactions << " transaction(s) deleted ✅";

    numTransactions = 0;
    transactionAmount = "";
}
