#include <iostream>
#include <vector>
#include <algorithm>

#include "Commands.hpp"
#include "Date.hpp"
#include "Warehouse.hpp"
#include <ctime>
int main() {
    Warehouse warehouse;

    std::vector<BaseCommand*> commands;
    commands.push_back(new HelpCommand());
    commands.push_back(new ExitCommand());
    commands.push_back(new OpenCommand(warehouse));
    commands.push_back(new CloseCommand(warehouse));
    commands.push_back(new SaveCommand(warehouse));
    commands.push_back(new SaveAsCommand(warehouse));   
    commands.push_back(new PrintCommand(warehouse));
    commands.push_back(new AddCommand(warehouse));
    commands.push_back(new RemoveCommand(warehouse));
    commands.push_back(new LogCommand(warehouse));
    commands.push_back(new CleanCommand(warehouse));

    std::string command;

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
// test 2000-05-05 2000-05-05 test kg 10 ee