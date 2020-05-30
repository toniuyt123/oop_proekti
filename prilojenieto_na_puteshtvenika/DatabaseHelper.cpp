#include <fstream>
#include <sstream>
#include <iostream>

#include "DatabaseHelper.hpp"

std::string DatabaseHelper::dbName = "users.db";

DatabaseHelper::DatabaseHelper() {};

bool DatabaseHelper::userExists(std::string username) {
    try {
        this->getUser(username);

        return true;
    } catch (const char* err) {
        return false;
    }
}

User DatabaseHelper::getUser(std::string username) {
    std::ifstream users(DatabaseHelper::dbName, std::ios::in);
    
    User user;
    std::string line;

    while (getline(users, line)) {
        std::istringstream stream;
        stream.str(line);
        stream >> user;

        if (user.getUsername() == username) {
            users.close();

            return user;
        }
    }

    users.close();
    throw "User not found";
}

void DatabaseHelper::recordUser(const User& user) {
    std::ofstream users(DatabaseHelper::dbName, std::ios::out|std::ios::app);
    users << user << std::endl;
    users.close();
}
