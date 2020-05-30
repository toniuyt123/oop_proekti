#include <string>
#include <sstream>
#include <iostream>

#include "User.hpp"
#include "Travel.hpp"

User::User() :loggedIn(false) {}
User::User(std::string username, std::string passwordHash, std::string email)
    : username(username), passwordHash(passwordHash), email(email) {}

std::string User::getUsername() const {
    return this->username;
}

std::string User::getPasswordHash() const {
    return this->passwordHash;
}

std::string User::getEmail() const {
    return this->email;
}

bool User::getLoggedIn() const {
    return this->loggedIn;
}

void User::setLoggedIn(bool loggedIn) {
    this->loggedIn = loggedIn;
}

bool User::checkCredentials(std::string username, std::string passwordHash) {
    return this->username == username && this->passwordHash == passwordHash;
}

void User::addFriend(std::string fr) {
    this->friends.push_back(fr);
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << user.username << " " << user.passwordHash << " " << user.email;

    for (auto& fr : user.friends) {
        os << " " << fr;
    }

    return os;
}

std::istream& operator>>(std::istream& is, User& user) {
    is >> user.username >> user.passwordHash >> user.email;

    std::string friends, fr;

    getline(is, friends);
    std::istringstream stream;
    stream.str(friends);

    while (stream >> fr) {

        user.addFriend(fr);
    }

    return is;
}