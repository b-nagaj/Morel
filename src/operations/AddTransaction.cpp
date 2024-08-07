#include "AddTransaction.hpp"

/**
 * Handles invoking the GetNewTransactions() and AddNewTransactions() functions
 */
void AddTransaction::Add() {
    GetNewTransactions();
    DisplayNewTransactions();
    // once the user has confirmed the operation, add the transactions
    if (confirmed) {
        AddNewTransactions();
    }
}

/**
 * accepts user input for new transactions, then adds them to an array once validated
 */ 
void AddTransaction::GetNewTransactions() {
    std::string uncheckedTransactionAmount;
    std::string uncheckedTransactionCategory;
    Date date;
    Date currentDate = date.GetCurrentDate();
    numNewTransactions = 0;

    // display instructions
    std::cout << "\nPlease give a list of new transactions"
              << "\nInclude each expense on a seperate line"
              << "\nType 'end' to indicate the end of the list\n\n";

    // prompt user for a transaction's amount & category until "end" is typed
    while (uncheckedTransactionAmount != "end") {
        std::cout << "Transaction" << " #" << (numNewTransactions + 2);

        std::cout << "\nAmount: ";
        std::getline(std::cin, uncheckedTransactionAmount);

        if (uncheckedTransactionAmount == "end") {
            break;
        }

        std::cout << "Category: ";
        std::getline(std::cin, uncheckedTransactionCategory);
        std::cout << "\n";

        // given the input is valid, instantiate a new transaction
        if (ValidateNewTransactionAmount(uncheckedTransactionAmount) && 
            ValidateNewTransactionCategory(uncheckedTransactionCategory)) {
            transactionAmount = uncheckedTransactionAmount;
            transactionCategory = uncheckedTransactionCategory;

            // TODO: Implement a way to retrieve the user id of the username 
            // you're using
            Transaction newTransaction(1, 
                                       transactionAmount, 
                                       transactionCategory, 
                                       currentDate);
            numNewTransactions++;
            // insert into array index 0 when numNewTransactions = 1, etc. etc.
            newTransactions[numNewTransactions - 1] = newTransaction;
        }
    }
}

/**
 * validates that user input for a transaction's amount isn't empty and doesn't
 * contain letters or special characters
 * 
 * @param uncheckedTransactionAmount an input value for a transaction's amount 
 * that hasn't been checked
 * @return a boolean value based on the correctness of a user's input
 */ 
bool AddTransaction::ValidateNewTransactionAmount(std::string uncheckedTransactionAmount) { 
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
bool AddTransaction::ValidateNewTransactionCategory(std::string uncheckedTransactionCategory) {
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
 * confirms whether the user would like to add the transaction
 * 
 * @return boolean value that represent's the user's input (yes or no)
 */
bool AddTransaction::ConfirmOperation() {
    // check that a user has entered at least 1 transaction
    if (numNewTransactions != 0) {
        std::string confirmationResponse = "";

        std::cout << "\nAdd the above transactions? (Y/N): ";
        std::getline(std::cin, confirmationResponse);

        if (confirmationResponse == "Y" || confirmationResponse == "y" ) {
            return true;
        }
        else {
            std::cout << "\n0 new Transaction(s) Added";
            return false;
        }
    }
    else {
        std::cout << "\n0 new Transaction(s) Added";
        return false;
    }
}

/*
 * displays the list of transactions entered by the user
*/
void AddTransaction::DisplayNewTransactions() {
    // display each transaction to the user in a readable format
    std::cout << "\n";
    for (int i = 0; i < numNewTransactions; i++) {
        std::cout << "$" 
                  << newTransactions[i].GetAmount() 
                  << " -> " 
                  << newTransactions[i].GetCategory() 
                  << "\n";
    }

    confirmed = ConfirmOperation();
}

/**
 * Invokes the CreateNewTransactions() function from DBManager to add a list
 * of transactions
 */
void AddTransaction::AddNewTransactions() {
    DBManager dbManager;

    dbManager.CreateNewTransactions(newTransactions, numNewTransactions);
    std::cout << "\n" << dbManager.GetNumAffectedRows() << " new Transaction(s) Added ✅";
    dbManager.SetNumAffectedRows(0);
}
