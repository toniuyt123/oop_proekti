#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#include "Date.hpp"
#include "Commands.hpp"
#include "User.hpp"

int main() {
    User user;
    DatabaseHelper dbh;
    std::string command;
    std::vector<BaseCommand*> commands;

    commands.push_back(new HelpCommand());
    commands.push_back(new ExitCommand());
    commands.push_back(new RegisterCommand(user, dbh));
    commands.push_back(new LoginCommand(user, dbh));
    commands.push_back(new TravelCommand(user, dbh));
    commands.push_back(new FriendCommand(user, dbh));
    commands.push_back(new BrowseCommand(user, dbh));
    commands.push_back(new ListCommand(user, dbh));
    commands.push_back(new ListGradesCommand(user, dbh));

    while (true) {
        try {
            std::cout << "Enter command: ";
            std::cin >> command;

            std::vector<BaseCommand*>::iterator pos = std::find_if(commands.begin(), commands.end(),
                    [&command](const BaseCommand* x) { return x->getName() == command; });
        
            if (pos != commands.end()) {
                (*pos)->execute();
            } else {
                std::cout << "Invalid command" << std::endl;
            }
        } catch (const char* err) {
            std::cout << err << std::endl;
        }
    }

    return 0;
}

//g++ main.cpp Commands.cpp Travel.cpp DatabaseHelper.cpp Date.cpp User.cpp
/*
Burgas, Bulgaria|2019-07-15|2019-07-29|5|A beautiful city on the Black Sea coast. I spent two unforgettable weeks there, meeting new people|burgas.jpeg locumfest.png sunrise_on_the_coast.jpeg|
*/
