#include <iostream>
#include <fstream>
#include <string>

#include "Commands.hpp"
#include "Warehouse.hpp"

std::string FileCommand::filename = "";

BaseCommand::BaseCommand(std::string name) : name(name) {};
FileCommand::FileCommand(std::string name, Warehouse& warehouse) : BaseCommand(name), warehouse(warehouse) {};
WarehouseCommand::WarehouseCommand(std::string name, Warehouse& warehouse) : BaseCommand(name), warehouse(warehouse) {};

HelpCommand::HelpCommand() : BaseCommand("help") {};
ExitCommand::ExitCommand() : BaseCommand("exit") {};

OpenCommand::OpenCommand(Warehouse& warehouse) : FileCommand("open", warehouse) {};
CloseCommand::CloseCommand(Warehouse& warehouse) : FileCommand("close", warehouse) {};
SaveCommand::SaveCommand(Warehouse& warehouse) : FileCommand("save", warehouse) {};
SaveAsCommand::SaveAsCommand(Warehouse& warehouse) : FileCommand("saveas", warehouse) {};

PrintCommand::PrintCommand(Warehouse& warehouse) : WarehouseCommand("print", warehouse) {};
AddCommand::AddCommand(Warehouse& warehouse) : WarehouseCommand("add", warehouse) {};
RemoveCommand::RemoveCommand(Warehouse& warehouse) : WarehouseCommand("remove", warehouse) {};
LogCommand::LogCommand(Warehouse& warehouse) : WarehouseCommand("log", warehouse) {};
CleanCommand::CleanCommand(Warehouse& warehouse) : WarehouseCommand("clean", warehouse) {};

std::string BaseCommand::getName() const {
    return this->name;
}

Warehouse& WarehouseCommand::getWarehouse() const {
    return this->warehouse;
}

void WarehouseCommand::setWarehouse(Warehouse& warehouse) {
    this->warehouse = warehouse;
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

        file.close();
    } else {
        throw "Currently there is an open file. Please close first";
    }
}

void CloseCommand::execute() {
    if (FileCommand::filename != "") {
        
    } else {
        throw "No file to close. Open first";
    }
}

void SaveCommand::execute() {
    
}

void SaveAsCommand::execute() {
    
}

void PrintCommand::execute() {
    
}

void AddCommand::execute() {
    
}

void RemoveCommand::execute() {
    
}

void LogCommand::execute() {
    
}

void CleanCommand::execute() {
    this->getWarehouse().clean();
}
