#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include "Warehouse.hpp"

class BaseCommand {
private:
    std::string name;
public:
    BaseCommand(std::string);

    std::string getName() const;

    virtual void execute() = 0;
};

class HelpCommand : public BaseCommand {
public:
    HelpCommand();

    void execute();
};

class ExitCommand : public BaseCommand {
public:
    ExitCommand();

    void execute();
};

class FileCommand : public BaseCommand {
private:
    Warehouse& warehouse;
protected:
    static std::string filename;
public:
    FileCommand(std::string, Warehouse&);

    Warehouse& getWarehouse() const;

    virtual void execute() = 0;
};

class OpenCommand : public FileCommand {
public:
    OpenCommand(Warehouse&);

    void execute();
};

class CloseCommand : public FileCommand {
public:
    CloseCommand(Warehouse&);

    void execute();
};

class SaveCommand : public FileCommand {
public:
    SaveCommand(Warehouse&);

    void execute();
};


class SaveAsCommand : public FileCommand {
public:
    SaveAsCommand(Warehouse&);

    void execute();
};

class PrintCommand : public FileCommand {
public:
    PrintCommand(Warehouse&);

    void execute();
};

class AddCommand : public FileCommand {
public:
    AddCommand(Warehouse&);

    void execute();
};

class RemoveCommand : public FileCommand {
public:
    RemoveCommand(Warehouse&);

    void execute();
};

class LogCommand : public FileCommand {
public:
    LogCommand(Warehouse&);

    void execute();
};

class CleanCommand : public FileCommand {
public:
    CleanCommand(Warehouse&);

    void execute();
};

#endif
