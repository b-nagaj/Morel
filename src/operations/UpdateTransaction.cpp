#include "UpdateTransaction.hpp"

/**
 * initializes class attributes
*/
UpdateTransaction::UpdateTransaction() {
    numTransactions = 0;
    updatedTransactionAmount = "";
    updatedTransactionCategory = "";
    transactionAmount = "";
    foundTransactions = nullptr;
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
 * invokes GetTransactionsByAmount() from DBManager to search the list of
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
    foundTransactions = dbManager.StoreFoundTransactions(dbManager.stmt, dbManager.result);

    // Display matching transactions
    for (int i = 0; i < dbManager.GetnumRowsReturned(); i++) {
        std::cout << "\nDate: " << foundTransactions[i].GetDate();
        std::cout << "\nAmount: $" << foundTransactions[i].GetAmount();
        std::cout << "\nCategory: " << foundTransactions[i].GetCategory();
        std::cout << std::endl;

        // add the current transaction to the list of transactions to be updated
        if (ConfirmOperation()) {
            transactions[i].SetTransactionID(foundTransactions[i].GetTransactionID());
            transactions[i].SetAmount(foundTransactions[i].GetAmount());
            transactions[i].SetCategory(foundTransactions[i].GetCategory());
            numTransactions++;

            // prompt the user to enter new information about the transaction
            GetNewTransactionInformation(i);
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
 * 
 * @param index the index that references a transaction that needs to be updated
 */
void UpdateTransaction::GetNewTransactionInformation(int index) {
    std::string uncheckedTransactionAmount;
    std::string uncheckedTransactionCategory;

    std::cout << "\nAmount: ";
    std::getline(std::cin, uncheckedTransactionAmount);

    std::cout << "Category: ";
    std::getline(std::cin, uncheckedTransactionCategory);
    std::cout << "\n";

    // given the input is valid, set the current transaction's attributes to
    // match the updated amount, category, and date values
    if (ValidateNewTransactionAmount(uncheckedTransactionAmount) && 
    ValidateNewTransactionCategory(uncheckedTransactionCategory)) {
        updatedTransactionAmount = uncheckedTransactionAmount;
        updatedTransactionCategory = uncheckedTransactionCategory;

        transactions[index].SetAmount(updatedTransactionAmount); 
        transactions[index].SetCategory(updatedTransactionCategory);
    }

    // reset placeholders
    updatedTransactionAmount = "";
    updatedTransactionCategory = "";
}

/**
 * validates that user input for a transaction's amount isn't empty and doesn't
 * contain letters or special characters
 * 
 * @param uncheckedTransactionAmount an input value for a transaction's amount 
 * that hasn't been checked
 * @return a boolean value based on the correctness of a user's input
 */ 
bool UpdateTransaction::ValidateNewTransactionAmount(std::string uncheckedTransactionAmount) { 
    // strip decimal character from transaction amount value   
    std::string transactionAmountWithoutDecimal = uncheckedTransactionAmount;
    transactionAmountWithoutDecimal.erase(remove(transactionAmountWithoutDecimal.begin(), 
                                                 transactionAmountWithoutDecimal.end(), 
                                                 '.'), 
                                                 transactionAmountWithoutDecimal.end());
    
    // check if the users input is empty
    if (uncheckedTransactionAmount.empty()) {
        std::cout << "ERROR: You entered an empty value for a transaction amount\n\n";
        return false;
    }
    // check if the users input is numeric
    else if (std::all_of(transactionAmountWithoutDecimal.begin(), 
                         transactionAmountWithoutDecimal.end(), 
                         ::isdigit) == false) {
        std::cout << "ERROR: '" 
                  << uncheckedTransactionAmount 
                  << "' is not a numerical value\n\n";
        return false;
    }
    else {
        return true; 
    }
}

/**
 * validates that user input for a transactions' category isn't empty and 
 * doesn't contain numerical values 
 * 
 * @param uncheckedTransactionCategory an input value for a transaction's 
 * category that hasn't been checked
 * @return a boolean value based on the correctness of a user's input
 */ 
bool UpdateTransaction::ValidateNewTransactionCategory(std::string uncheckedTransactionCategory) {
    // check if the users input is empty
    if (uncheckedTransactionCategory.empty()) {
        std::cout << "ERROR: You entered an empty value for a transaction category\n\n";
        return false;
    }

    // check if the users input contains anything other than letters or spaces
    for (char ch : uncheckedTransactionCategory) {
        if (!std::isalpha(ch) && ch != ' ') {
            std::cout << "ERROR: Category names must only contain letters or spaces\n\n";
            return false;
        }
    }

    return true;
}

/**
 * updates the transaction or list of transactions the user has agreed to update
 * by invoking the DBManager's UpdateTransaction() function
*/
void UpdateTransaction::UpdateTheTransactions() {
    for (int i = 0; i < numTransactions; i++) {
        dbManager.UpdateTransaction(transactions[i]);
    }

    std::cout << "\n" << dbManager.GetNumAffectedRows() << " transaction(s) updated ✅";
    dbManager.SetNumAffectedRows(0);
}
