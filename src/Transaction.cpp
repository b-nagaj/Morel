#include <sstream>
#include <iomanip>

#include "../lib/Transaction.hpp"

Transaction::Transaction(int id, double a, std::string c, std::string td) {
    userID = id;
    amount = a;
    category = c;
    transactionDate = td;
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
    amount = FormatAmountToDecimal(a);
}

std::string Transaction::GetCategory() {
    return category;
}

void Transaction::SetCategory(std::string c) {
    category = c;
}

std::string Transaction::FormatAmountToDecimal(std::string value) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value;
    return ss.str();
}
