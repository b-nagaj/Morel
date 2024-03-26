#include "DeleteTransaction.hpp"

void DeleteTransaction::Delete() {
    GetTransaction();
    FindTransaction();
}

void DeleteTransaction::GetTransaction() {
    std::cout << "\nPlease enter the amount for a transaction you'd like to delete\n\n";
    std::cout << "Transaction Amount: ";
    std::cin >> transactionAmount;
}

bool DeleteTransaction::FindTransaction() {
    DBManager dbManager;

    if (dbManager.Connect()) {
        dbManager.GetTransactionByAmount(transactionAmount);
        dbManager.Disconnect();
    }
    else {
        std::cout << "\nERROR: Could not connect to database\n\n";
    }
}

bool DeleteTransaction::ConfirmOperation() {

}

void DeleteTransaction::DeleteTheTransaction() {

}
