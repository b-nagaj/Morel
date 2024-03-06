#include "Transaction.hpp"

/**
 * Default constructor that initializes each class attribute with '0' or ""
 */
Transaction::Transaction() {
    SetUserID(0);
    SetAmount("");
    SetCategory("");
    Date date(0, 0, 0);
    SetTransactionDate(date);
}

/**
 * Alternate constructor that initializes each class attribute based on input parameters
 * 
 * @param id value to set userID equal to
 * @param a value to set amount equal to
 * @param c value to set category equal to
 * @param td value to set transactionDate equal to
 */
Transaction::Transaction(int id, std::string a, std::string c, Date td) {
    SetUserID(id);
    SetAmount(a);
    SetCategory(c);
    SetTransactionDate(td);
}

// Getters

/**
 * Gets transaction userID
 * 
 * @return userID
 */
int Transaction::GetUserID() {
    return userID;
}

/**
 * Gets transaction amount
 * 
 * @return amount
 */
std::string Transaction::GetAmount() {
    return amount;
}

/**
 * Gets transaction category
 * 
 * @return category
 */
std::string Transaction::GetCategory() {
    return category;
}

/**
 * Gets transaction date
 * 
 * @return transactionDate
 */
std::string Transaction::GetTransactionDate() {
    return transactionDate;
}

// Setters

/**
 * Sets transaction userID
 */
void Transaction::SetUserID(int id) {
    userID = id;
}

/**
 * Sets transaction amount
 */
void Transaction::SetAmount(std::string a) {
    amount = a;
}

/**
 * Sets transaction category
 */
void Transaction::SetCategory(std::string c) {
    category = c;
}

/**
 * Sets transaction date
 */
void Transaction::SetTransactionDate(Date date) {
    transactionDate = date.FormatToTimestamp();
}
