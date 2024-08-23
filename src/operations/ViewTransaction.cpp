#include "ViewTransaction.hpp"

/**
 * Initialize class attributes
 */
ViewTransaction::ViewTransaction() {
    lesserDate = "";
    greaterDate = "";
}

/**
 * Handles invoking the appropriate class methods to :
 *  - accept user input for a date range
 *  - invoke the DBManager to search for those transactions
 *  - display the found transactions back to the user
 */
void ViewTransaction::View() {
    if (GetDateRange() && FindTransactions()) {
        DisplayTransactions();
    }
}

/**
 * Accepts input from the user that represents a date range
 */
bool ViewTransaction::GetDateRange() {
    // Prompt for the first date
    std::cout << "\nPlease enter a date range for transactions you'd like to see"
            
              << "\n\nSearch for transactions from: ";
    std::getline(std::cin, lesserDate);

    // Prompt the user for the second date
    std::cout << "                          to: ";
    std::getline(std::cin, greaterDate);

    if (ConfirmOperation()) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Confirm with the user that the date range they provided is correct
 */
bool ViewTransaction::ConfirmOperation() {
    std::string confirmationResponse = "";
    std::cout << "\n\nView Transactions from " 
              << lesserDate 
              << " to " 
              << greaterDate 
              << "? (Y/N)";
    std::getline(std::cin, confirmationResponse);

    if (confirmationResponse == "Y" || confirmationResponse == "y" ) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Invokes the DBManager to search for transactions that fall within the
 * date range provided by the user
 */
bool ViewTransaction::FindTransactions() {
    return dbManager.GetTransactionsByDate(lesserDate, greaterDate);
}

/**
 * Displays the transactions that fall within the date range provided by the user
 */
void ViewTransaction::DisplayTransactions() {
    transactions = dbManager.StoreFoundTransactions(dbManager.stmt, dbManager.result);

    // Display matching transactions
    for (int i = 0; i < dbManager.GetnumRowsReturned(); i++) {
        std::cout << transactions[i].GetDate()
                  << " "
                  << transactions[i].GetAmount()
                  << " "
                  << transactions[i].GetCategory();
        std::cout << std::endl;
    }
}
