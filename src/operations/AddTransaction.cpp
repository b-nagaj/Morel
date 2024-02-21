#include "AddTransaction.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <mysql/mysql.h>
#include <cctype>

void AddTransaction::Add() {
    GetNewTransactions();
    AddNewTransactions();
}

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
        if (ValidateNewTransactionAmount(uncheckedTransactionAmount) && ValidateNewTransactionCategory(uncheckedTransactionCategory)) {
            transactionAmount = uncheckedTransactionAmount;
            transactionCategory = uncheckedTransactionCategory;

            // TODO: Implement a way to retrieve the user id of the username you're using
            Transaction newTransaction(1, transactionAmount, transactionCategory, GetCurrentDate());
            newTransactions[numNewTransactions] = newTransaction;
        }
    }
}

bool AddTransaction::ValidateNewTransactionAmount(std::string uncheckedTransactionAmount) { 
    // strip decimal character from transaction amount value   
    std::string transactionAmountWithoutDecimal = uncheckedTransactionAmount;
    transactionAmountWithoutDecimal.erase(remove(transactionAmountWithoutDecimal.begin(), transactionAmountWithoutDecimal.end(), '.'), transactionAmountWithoutDecimal.end());
    
    // check if the users input is empty
    if (uncheckedTransactionAmount.empty()) {
        std::cout << "\nERROR: You entered an empty value for a transaction amount\n\n";
        return false;
    }
    // check if the users input is numeric
    else if (std::all_of(transactionAmountWithoutDecimal.begin(), transactionAmountWithoutDecimal.end(), ::isdigit) == false) {
        std::cout << "\nERROR: '" << uncheckedTransactionAmount << "' is not a numerical value\n\n";
        return false;
    }
    else {
        return true; 
    }
}

// TODO: This is broken
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

void AddTransaction::AddNewTransactions() {
    // establish a MySQL connection & report connection exceptions
    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        std::cerr << "Error initializing MySQL connection" << std::endl;
    }
    // TODO: Retrieve these credentials with AWS Secrets Manager API
    if (!mysql_real_connect(con, "dbName", "dbUsername", "dbPassword", "Morel", 3306, NULL, 0)) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(con) << std::endl;
        mysql_close(con);
    }

    // execute INSERT queries for each new transaction
    for (int i = 0; i < numNewTransactions; i++) {
        std::string query = "INSERT INTO Transactions(user_id, amount, category, transaction_date) VALUES ('" +
                            std::to_string(newTransactions[i].GetUserID()) + "', '" +
                            newTransactions[i].GetAmount() + "', '" +
                            newTransactions[i].GetCategory() + "', '" +
                            newTransactions[i].GetTransactionDate() + "')";
        // handle exceptions
        if (mysql_query(con, query.c_str()) != 0) {
            std::cerr << "Error executing SQL query: " << mysql_error(con) << std::endl;
            mysql_close(con);
        }
    }

    // Close MySQL connection
    mysql_close(con);
}
