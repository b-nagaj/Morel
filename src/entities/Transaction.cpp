#include "Transaction.hpp"

Transaction::Transaction() {
    SetUserID(0);
    SetAmount("");
    SetCategory("");
    Date date(0, 0, 0);
    SetDate(date);
}

Transaction::Transaction(int id, std::string a, std::string c, Date td) {
    SetUserID(id);
    SetAmount(a);
    SetCategory(c);
    SetDate(td);
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

std::string Transaction::GetDate() {
    return transactionDate;
}

// Setters

void Transaction::SetUserID(int id) {
    userID = id;
}

void Transaction::SetAmount(std::string a) {
    amount = a;
}

void Transaction::SetCategory(std::string c) {
    category = c;
}

void Transaction::SetDate(Date date) {
    transactionDate = date.FormatToTimestamp();
}
