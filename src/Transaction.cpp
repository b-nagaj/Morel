#include <sstream>
#include <iomanip>

#include "../lib/Transaction.hpp"

Transaction::Transaction(int id, std::string a, std::string c, Date td) {
    SetUserID(id);
    SetAmount(a);
    SetCategory(c);
    SetTransactionDate(td);
}

std::string Transaction::GetTransactionDate() {
    return transactionDate;
}

void Transaction::SetTransactionDate(Date date) {
    transactionDate = date.FormatToTimestamp();
}

int Transaction::GetUserID() {
    return userID;
}

void Transaction::SetUserID(int id) {
    userID = id;
}

std::string Transaction::GetAmount() {
    return amount;
}

void Transaction::SetAmount(std::string a) {
    amount = FormatToDecimal(a);
}

std::string Transaction::GetCategory() {
    return category;
}

void Transaction::SetCategory(std::string c) {
    category = c;
}

std::string Transaction::FormatToDecimal(std::string value) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value;
    return ss.str();
}
