#include "User.hpp"

/**
 * alternate constructor that initializes a user's username
 * 
 * @param username a user's username
 */ 
User::User(std::string username) {
    SetUsername(username);
}

/** 
 * retrieves a user's username
 * 
 * @return a user's username
 */ 
std::string User::GetUsername() {
    return username;
}

/**
 * sets a user's username
 * 
 * @param u a user's username
 */ 
void User::SetUsername(std::string u) {
    username = u;
}
