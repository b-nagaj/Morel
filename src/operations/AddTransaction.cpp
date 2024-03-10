#include "AddTransaction.hpp"
#include "../utils/DBManager.hpp"

void AddTransaction::Add() {
    GetNewTransactions();
    AddNewTransactions();
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
    Date date((tm_now->tm_mon + 1), (tm_now->tm_mday), (tm_now->tm_year + 1900));
    
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
        std::cin >> uncheckedTransactionAmount;
        numNewTransactions++;
        if (uncheckedTransactionAmount == "end") {
            break;
        }
        std::cout << "Category: ";
        std::cin >> uncheckedTransactionCategory;
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
 * validates that user input for a transaction's amount isn't empty, and doesn't
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
 * invokes the CreateNewTransactions() method from DBManager to add an array of 
 * transactions to the DB
 */ 
void AddTransaction::AddNewTransactions() {
    DBManager dbManager;
    
    if (dbManager.Connect()) {
        dbManager.CreateNewTransactions(newTransactions, numNewTransactions);
        dbManager.Disconnect();
        std::cout << "\n" << numNewTransactions << " new Transaction(s) Added ✅";
    }
    else {
        std::cout << "\nERROR: Could not connect to database\n\n";
    }
}
