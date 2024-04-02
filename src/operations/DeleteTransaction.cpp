#include "DeleteTransaction.hpp"

/**
 * initializes class attributes
*/
DeleteTransaction::DeleteTransaction() {
    numTransactions = 0;
    transactionAmount = "";
}

/**
 * handles invoking GetTransaction() and DeleteTheTransaction() methods
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
    std::cin >> transactionAmount;
}

/**
 * invokes the GetTransactionByAmount DBManager function to search the list of
 * transactions based on the user provided transaction amount
 * 
 * @return true or false based on if a transaction was found
*/
bool DeleteTransaction::FindTransaction() {
    DBManager dbManager;
    long numRows;

    result = dbManager.GetTransactionByAmount(transactionAmount);
    numRows = mysql_num_rows(result);
    mysql_free_result(result);

    if (numRows < 1) {
        std::cout << "\nERROR: No transactions with an amount of $"
                  << transactionAmount
                  << " exist";
        return false;
    }
    else {
        return true;
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
    std::cin >> confirmationResponse;

    if (confirmationResponse == "Y" || confirmationResponse == "y" ) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * displays each transaction that matches the user provided transaction amount,
 * then prompts the user by invoking ConfirmOperation() for each transaction found
*/
void DeleteTransaction::DisplayTransaction() {
    MYSQL_ROW row;
    
    // display each transaction that matches the transactionAmount
    while ((row = mysql_fetch_row(result)) != NULL) {
        std::cout << "\nDate: " << (row[4] ? row[4] : "NULL");
        std::cout << "\nAmount: $" << (row[2] ? row[2] : "NULL");
        std::cout << "\nCategory: " << (row[3] ? row[3] : "NULL");
        std::cout << std::endl;

        std::string transactionID = row[0];

        if (ConfirmOperation()) {
            transactionIDs[numTransactions] = transactionID;
            numTransactions++;
        }
    }
}

/**
 * Deletes the transaction or list of transactions the user has agreed to delete
 * by invoking the DeleteTransaction() DBManager function
*/
void DeleteTransaction::DeleteTheTransaction() {
    DBManager dbManager;

    // delete each transaction based on the collection of transactionIDs
    for (int i = 0; i < numTransactions; i++) {
        dbManager.DeleteTransaction(transactionIDs[i]);
    }
    std::cout << "\n" << numTransactions << " transaction(s) deleted ✅";

    numTransactions = 0;
    transactionAmount = "";
}
