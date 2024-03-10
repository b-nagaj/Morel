#include "User.hpp"

/**
 * initializes a user's username
 * 
 * @param username
 */ 
User::User(std::string username) {
    SetUsername(username);
}

/** 
 * gets a user's username
 * 
 * @return username
 */ 
std::string User::GetUsername() {
    return username;
}

/**
 * sets a user's username
 * 
 * @param u
 */ 
void User::SetUsername(std::string u) {
    username = u;
}
