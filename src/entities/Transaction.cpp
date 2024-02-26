#include "Transaction.hpp"

Transaction::Transaction() {
    SetUserID(0);
    SetAmount("");
    SetCategory("");
    Date date(0, 0, 0);
    SetTransactionDate(date);
}

Transaction::Transaction(int id, std::string a, std::string c, Date td) {
    SetUserID(id);
    SetAmount(a);
    SetCategory(c);
    SetTransactionDate(td);
}

// helper function to format a transaction amount to currency format
std::string FormatToDecimal(std::string value) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value;
    return ss.str();
}

// Getters

int Transaction::GetUserID() {
    return userID;
}

std::string Transaction::GetAmount() {
    return amount;
}

std::string Transaction::GetCategory() {
    return category;
}

std::string Transaction::GetTransactionDate() {
    return transactionDate;
}

// Setters

void Transaction::SetUserID(int id) {
    userID = id;
}

void Transaction::SetAmount(std::string a) {
    amount = FormatToDecimal(a);
}

void Transaction::SetCategory(std::string c) {
    category = c;
}

void Transaction::SetTransactionDate(Date date) {
    transactionDate = date.FormatToTimestamp();
}
