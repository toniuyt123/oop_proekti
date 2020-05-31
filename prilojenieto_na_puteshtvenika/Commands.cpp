#include <iostream>
#include <fstream>
#include <string>

#include "Commands.hpp"
#include "User.hpp"
#include "Travel.hpp"

BaseCommand::BaseCommand(std::string name) : name(name) {};
UserCommand::UserCommand(std::string name, User& user, DatabaseHelper& dbh) : BaseCommand(name), user(user), dbh(dbh) {};

HelpCommand::HelpCommand() : BaseCommand("help") {};
ExitCommand::ExitCommand() : BaseCommand("exit") {};

RegisterCommand::RegisterCommand(User& user, DatabaseHelper& dbh) : UserCommand("register", user, dbh) {};
LoginCommand::LoginCommand(User& user, DatabaseHelper& dbh) : UserCommand("login", user, dbh) {};
TravelCommand::TravelCommand(User& user, DatabaseHelper& dbh) : UserCommand("travel", user, dbh) {};
FriendCommand::FriendCommand(User& user, DatabaseHelper& dbh) : UserCommand("friend", user, dbh) {};
BrowseCommand::BrowseCommand(User& user, DatabaseHelper& dbh) : UserCommand("browse", user, dbh) {};

std::string BaseCommand::getName() const {
    return this->name;
}

User& UserCommand::getUser() const {
    return this->user;
}

void HelpCommand::execute() {
    std::cout << "The following   commands are supported:" << std::endl;
    std::cout << "help         prints this information" << std::endl;
    std::cout << "exit         exists the program" << std::endl;
    std::cout << "register     register new user" << std::endl;
    std::cout << "login        login to existing user" << std::endl;
    std::cout << "travel       record oen of your travels." << std::endl;
}

void ExitCommand::execute() {
    exit(0);
}

void RegisterCommand::execute() {
    if ( ! this->user.getLoggedIn()) {
        bool taken = false;
        std::string username, password, email;
        
        do {
            std::cout << "Enter username: ";
            std::cin >> username;

        } while(this->dbh.userExists(username));

        std::cout << "Enter password: ";
        std::cin >> password;
        std::cout << "Enter email: ";
        std::cin >> email;

        this->user = User(username, password, email);
        this->dbh.recordUser(this->user);

        std::cout << "Registered successfully!";
    } else {
        throw "Currently logged in";
    }
}

void LoginCommand::execute() {
    if ( ! this->user.getLoggedIn()) {
        std::string username, password;
        
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        this->user = this->dbh.getUser(username);

        if (this->user.checkCredentials(username, password)) {
            this->user.setLoggedIn(true);
        } else {
            this->user = User();

            throw "Invalid username or password";
        }

        std::cout << "Loged in!";
    } else {
        throw "Already logged in";
    }
}

void TravelCommand::execute() {
    if (this->user.getLoggedIn()) {
        Travel travel;

        std::cin >> travel;

        this->dbh.recordTravel(this->user, travel);
    } else {
        throw "Not logged in";
    }
}

void BrowseCommand::execute() {
    for (auto& fr : this->user.getFriends()) {
        std::vector<Travel> travels = this->dbh.getTravels(fr);

        for (auto& travel : travels) {
            std::cout << fr << " traveled to ";
            travel.print();
        }
    }
}

void FriendCommand::execute() {
    if (this->user.getLoggedIn()) {
        std::string name;
        
        std::cout << "Enter friend name";
        std::cin >> name;

        this->user.addFriend(name);
        this->dbh.addFriend(this->user, name);
    } else {
        throw "Not logged in";
    }
}
