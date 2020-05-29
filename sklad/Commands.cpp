#include <iostream>
#include <fstream>
#include <string>

#include "Commands.hpp"
#include "Warehouse.hpp"

std::string FileCommand::filename = "";

BaseCommand::BaseCommand(std::string name) : name(name) {};
FileCommand::FileCommand(std::string name, Warehouse& warehouse) : BaseCommand(name), warehouse(warehouse) {};

HelpCommand::HelpCommand() : BaseCommand("help") {};
ExitCommand::ExitCommand() : BaseCommand("exit") {};

OpenCommand::OpenCommand(Warehouse& warehouse) : FileCommand("open", warehouse) {};
CloseCommand::CloseCommand(Warehouse& warehouse) : FileCommand("close", warehouse) {};
SaveCommand::SaveCommand(Warehouse& warehouse) : FileCommand("save", warehouse) {};
SaveAsCommand::SaveAsCommand(Warehouse& warehouse) : FileCommand("saveas", warehouse) {};

PrintCommand::PrintCommand(Warehouse& warehouse) : FileCommand("print", warehouse) {};
AddCommand::AddCommand(Warehouse& warehouse) : FileCommand("add", warehouse) {};
RemoveCommand::RemoveCommand(Warehouse& warehouse) : FileCommand("remove", warehouse) {};
LogCommand::LogCommand(Warehouse& warehouse) : FileCommand("log", warehouse) {};
CleanCommand::CleanCommand(Warehouse& warehouse) : FileCommand("clean", warehouse) {};

std::string BaseCommand::getName() const {
    return this->name;
}

Warehouse& FileCommand::getWarehouse() const {
    return this->warehouse;
}

void HelpCommand::execute() {
    std::cout << "The following   commands are supported:" << std::endl;
    std::cout << "open <file>     opens <file>" << std::endl;
    std::cout << "close           closes currently opened file" << std::endl;
    std::cout << "save            saves the currently open file" << std::endl;
    std::cout << "saveas <file>   saves the currently open file in <file>" << std::endl;
    std::cout << "help            prints this information" << std::endl;
    std::cout << "exit            exists the program" << std::endl;
  
    std::cout << "print           prints warehouse information" << std::endl;
    std::cout << "add <Item>      adds item to warehouse. Checks for valid data" << std::endl;
    std::cout << "remove          removes item from warehouse by given anem and quantity" << std::endl;
    std::cout << "log <from> <to> prints all operation between dates <from> and <to>" << std::endl;
    std::cout << "clean           removes all items whose expiration dates have passed"  << std::endl;
}

void ExitCommand::execute() {
    exit(0);
}

void OpenCommand::execute() {
    if (FileCommand::filename == "") {
        std::cin >> FileCommand::filename;

        std::ifstream file(FileCommand::filename, std::ios::in);

        this->getWarehouse().fromFile(file);

        file.close();
    } else {
        throw "Currently there is an open file. Please close first";
    }
}

void CloseCommand::execute() {
    if (FileCommand::filename != "") {
        std::ofstream file(FileCommand::filename, std::ios::out);

        this->filename = "";

        file.close();
    } else {
        throw "No file to close. Open first";
    }
}

void SaveCommand::execute() {
    if (FileCommand::filename != "") {
        std::ofstream file(FileCommand::filename, std::ios::out);

        this->getWarehouse().toFile(file);

        file.close();
    } else {
        throw "No file opened. Open first";
    }
}

void SaveAsCommand::execute() {
    if (FileCommand::filename != "") {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;

        std::ofstream file(filename, std::ios::out);

        this->getWarehouse().toFile(file);

        file.close();
    } else {
        throw "No file opened. Open first";
    }
}

void PrintCommand::execute() {
    this->getWarehouse().print();
}

void AddCommand::execute() {
    if (FileCommand::filename != "") {
        Item item;
        std::cin >> item;

        this->getWarehouse().addItem(item);
    } else {
        throw "No file opened. Open first";
    }
}

void RemoveCommand::execute() {
    if (FileCommand::filename != "") {
        std::string name;
        int quantity;

        std::cout << "Enter name: ";
        std::cin >> name;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;

        this->getWarehouse().removeItem(name, quantity);;
    } else {
        throw "No file opened. Open first";
    }
}

void LogCommand::execute() {
    if (FileCommand::filename != "") {
        Date start, end;
        std::cout << "Enter start date (YYYY-MM-DD): ";
        std::cin >> start;
        std::cout << "Enter end date (YYYY-MM-DD): ";
        std::cin >> end;

        this->getWarehouse().log(start, end);
    } else {
        throw "No file opened. Open first";
    }
}

void CleanCommand::execute() {
    this->getWarehouse().clean();
}
