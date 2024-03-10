#include "Transaction.hpp"

/**
 * initializes each class attribute with '0' or ""
 */
Transaction::Transaction() {
    SetUserID(0);
    SetAmount("");
    SetCategory("");
    Date date(0, 0, 0);
    SetTransactionDate(date);
}

/**
 * initializes each class attribute based on input parameters
 * 
 * @param id the user a transaction should be created for
 * @param a a transaction's amount
 * @param c a transaction's category
 * @param td a transaction's date
 */
Transaction::Transaction(int id, std::string a, std::string c, Date td) {
    SetUserID(id);
    SetAmount(a);
    SetCategory(c);
    SetTransactionDate(td);
}

/**
 * Gets a transaction's userID
 * 
 * @return userID
 */
int Transaction::GetUserID() {
    return userID;
}

/**
 * Gets a transaction's amount
 * 
 * @return amount
 */
std::string Transaction::GetAmount() {
    return amount;
}

/**
 * Gets a transaction's category
 * 
 * @return category
 */
std::string Transaction::GetCategory() {
    return category;
}

/**
 * Gets a transaction's date
 * 
 * @return transactionDate
 */
std::string Transaction::GetTransactionDate() {
    return transactionDate;
}

// Setters

/**
 * Sets a transaction's userID
 */
void Transaction::SetUserID(int id) {
    userID = id;
}

/**
 * Sets a transaction's amount
 */
void Transaction::SetAmount(std::string a) {
    amount = a;
}

/**
 * Sets a transaction's category
 */
void Transaction::SetCategory(std::string c) {
    category = c;
}

/**
 * Sets a transaction's date
 */
void Transaction::SetTransactionDate(Date date) {
    transactionDate = date.FormatToTimestamp();
}
