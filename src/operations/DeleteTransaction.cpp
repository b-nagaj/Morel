#include "DeleteTransaction.hpp"

DeleteTransaction::DeleteTransaction() {
    numTransactions = 0;
    transactionAmount = "";
}

void DeleteTransaction::Delete() {
    GetTransaction();
    if (FindTransaction()) {
        DisplayTransaction();
        DeleteTheTransaction();
    }
}

void DeleteTransaction::GetTransaction() {
    std::cout << "\nPlease enter the amount for a transaction you'd like to delete\n\n";
    std::cout << "Transaction Amount: ";
    std::cin >> transactionAmount;
}

bool DeleteTransaction::FindTransaction() {
    DBManager dbManager;
    long numRows;

    if (dbManager.Connect()) {
        result = dbManager.GetTransactionByAmount(transactionAmount);
        numRows = mysql_num_rows(result);
        mysql_free_result(result);
        dbManager.Disconnect();
    }
    else {
        std::cout << "\nERROR: Could not connect to database\n\n";
    }

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

void DeleteTransaction::DeleteTheTransaction() {
    DBManager dbManager;

    if (dbManager.Connect()) {
        for (int i = 0; i < numTransactions; i++) {
            dbManager.DeleteTransaction(transactionIDs[i]);
        }
        std::cout << "\n" << numTransactions << " transaction(s) deleted ✅";

        dbManager.Disconnect();
    }
    else {
        std::cout << "\nERROR: Could not connect to database\n\n";
    }

    numTransactions = 0;
    transactionAmount = "";
}
