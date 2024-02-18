#include "User.hpp"

User::User(std::string username) {
    SetUsername(username);
}

std::string User::GetUsername() {
    return username;
}

void User::SetUsername(std::string u) {
    username = u;
}
