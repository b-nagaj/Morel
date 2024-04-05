#include "AddTransaction.hpp"

/**
 * Handles invoking the GetNewTransactions() and AddNewTransactions() functions
 */
void AddTransaction::Add() {
    GetNewTransactions();
    // confirms with user before performing the create operation
    if (ConfirmOperation()) {
        AddNewTransactions();
    }
}

/**
 * gets the current date and instantiates a new Date object
 * 
 * @return an instantiated date object with a month, day, and year value
 */
Date GetCurrentDate() {
    // get the current system time
    auto now = std::chrono::system_clock::now();
    // convert the system time to a time_t object
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    // convert the time_t object to a struct tm (broken down time)
    std::tm *tm_now = std::localtime(&time_now);
    // instantiate a new Date object
    Date date((tm_now->tm_mon + 1), tm_now->tm_mday, (tm_now->tm_year + 1900));
    
    return date;
}

/**
 * accepts user input for new transactions, then adds them to an array once validated
 */ 
void AddTransaction::GetNewTransactions() {
    std::string uncheckedTransactionAmount;
    std::string uncheckedTransactionCategory;
    numNewTransactions = -1;

    // display instructions
    std::cout << "\nPlease give a list of new transactions"
              << "\nInclude each expense on a seperate line"
              << "\nType 'end' to indicate the end of the list\n\n";

    // prompt user for a transaction's amount & category until "end" is typed
    while (uncheckedTransactionAmount != "end") {
        std::cout << "Transaction" << " #" << (numNewTransactions + 2);
        std::cout << "\nAmount: ";
        std::getline(std::cin, uncheckedTransactionAmount);
        numNewTransactions++;
        if (uncheckedTransactionAmount == "end") {
            break;
        }
        std::cout << "Category: ";
        std::getline(std::cin, uncheckedTransactionCategory);
        std::cout << "\n";

        // given the input is valid, instantiate a new transaction
        if (ValidateNewTransactionAmount(uncheckedTransactionAmount) 
            && ValidateNewTransactionCategory(uncheckedTransactionCategory)) {
            transactionAmount = uncheckedTransactionAmount;
            transactionCategory = uncheckedTransactionCategory;

            // TODO: Implement a way to retrieve the user id of the username 
            // you're using
            Transaction newTransaction(1, 
                                       transactionAmount, 
                                       transactionCategory, 
                                       GetCurrentDate());
            newTransactions[numNewTransactions] = newTransaction;
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
        std::cout << "\nERROR: You entered an empty value for a transaction" 
                  << "amount\n\n";
        return false;
    }
    // check if the users input is numeric
    else if (std::all_of(transactionAmountWithoutDecimal.begin(), 
                         transactionAmountWithoutDecimal.end(), 
                         ::isdigit) == false) {
        std::cout << "\nERROR: '" 
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
        return false;
    }
    // check if the users input contains anything other than letters
    for (char ch : uncheckedTransactionCategory) {
        if (!std::isalpha(ch)) {
            return false;
        }
    }

    return true; 
}

/**
 * Displays a summary of the user's input and asks them to confirm its correctness
 * 
 * @return boolean value that represent's the user's input (yes or no)
 */
bool AddTransaction::ConfirmOperation() {
    std::string confirmationResponse = "";

    // check that a user has entered at least 1 transaction, then display a
    // confirmation message
    if (numNewTransactions != 0) {
        // grab each transaction's amount & category from the array of new transactions
        // then display them to the user in a readable format
        std::cout << "\n";
        for (int i = 0; i < numNewTransactions; i++) {
            std::cout << "$" 
                    << newTransactions[i].GetAmount() 
                    << " -> " 
                    << newTransactions[i].GetCategory() 
                    << "\n";
        }

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

/**
 * Invokes the CreateNewTransactions() function from DBManager to delete a transaction
 * or list of transactions
 */
void AddTransaction::AddNewTransactions() {
    DBManager dbManager;

    dbManager.CreateNewTransactions(newTransactions, numNewTransactions);
    std::cout << "\n" << numNewTransactions << " new Transaction(s) Added ✅";
}
