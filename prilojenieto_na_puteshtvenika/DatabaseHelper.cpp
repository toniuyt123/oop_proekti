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

void DatabaseHelper::recordTravel(const User& user, const Travel& travel) {
    std::ofstream travels(user.getUsername() + ".db", std::ios::out|std::ios::app);
    travels << travel << std::endl;
    travels.close();
}

std::vector<Travel> DatabaseHelper::getTravels(std::string username) {
    std::ifstream travelsFile(username + ".db", std::ios::in);
    std::vector<Travel> travels;
    std::string line;
    Travel t;

    while(std::getline(travelsFile, line)) {
        std::istringstream stream;
        stream.str(line);
        stream >> t;
        std::cout << "Travel read : " << t.getDestination() << std::endl;
        travels.push_back(t);
    }

    travelsFile.close();

    return travels;
}

void DatabaseHelper::addFriend(const User& user, std::string fr) {
    std::ifstream users(DatabaseHelper::dbName, std::ios::in);
    std::vector<std::string> lines;
    std::string line;

    while(std::getline(users, line)) {
        lines.push_back(line);
    }
    users.close();

    std::ofstream updated(DatabaseHelper::dbName, std::ios::out);

    for (auto& l : lines) {
        std::string usr = l.substr(0, l.find(' '));

        if (usr == user.getUsername()) {
            l += (" " + fr);
        }
        
        updated << l << std::endl;
    }
}