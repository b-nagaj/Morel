#include "DeleteTransaction.hpp"

void DeleteTransaction::Delete() {
    GetTransaction();
    FindTransaction();
    if (ConfirmOperation()) {
        DeleteTheTransaction();
    };
}

void DeleteTransaction::GetTransaction() {
    std::cout << "\nPlease enter the amount for a transaction you'd like to delete\n\n";
    std::cout << "Transaction Amount: ";
    std::cin >> transactionAmount;
}

bool DeleteTransaction::FindTransaction() {
    DBManager dbManager;

    if (dbManager.Connect()) {
        result = dbManager.GetTransactionByAmount(transactionAmount);
        mysql_free_result(result);
        dbManager.Disconnect();
    }
    else {
        std::cout << "\nERROR: Could not connect to database\n\n";
    }
}

bool DeleteTransaction::ConfirmOperation() {
    std::string confirmationResponse = "";
    long numRows = mysql_num_rows(result);

    if (numRows < 1) {
        std::cout << "\nERROR: No transactions with an amount of "
                  << transactionAmount
                  << " exist";
        return false;
    }
    else {
        DisplayTransaction();

        std::cout << "\nDelete the above transaction? (Y/N): ";
        std::cin >> confirmationResponse;

        if (confirmationResponse == "Y" || confirmationResponse == "y" ) {
            return true;
        }
        else {
            std::cout << "\n0 new Transaction(s) Added";
            return false;
        }
    }
}

void DeleteTransaction::DisplayTransaction() {
    MYSQL_ROW row;
    
    // display each transaction that matches the transactionAmount
    while ((row = mysql_fetch_row(result)) != NULL) {
        std::cout << "\nDate: " << (row[0] ? row[0] : "NULL");
        std::cout << "\nAmount: $" << (row[1] ? row[1] : "NULL");
        std::cout << "\nCategory: " << (row[2] ? row[2] : "NULL");
        std::cout << std::endl;
    }
}

void DeleteTransaction::DeleteTheTransaction() {
    DBManager dbManager;

    if (dbManager.Connect()) {
        dbManager.DeleteTransaction(transactionAmount);
        std::cout << "\n" 
                  << "The transaction with an amount of " 
                  << transactionAmount 
                  << " was deleted ✅";
        dbManager.Disconnect();
    }
    else {
        std::cout << "\nERROR: Could not connect to database\n\n";
    }
}
