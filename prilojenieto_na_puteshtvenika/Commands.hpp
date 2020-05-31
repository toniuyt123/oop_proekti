#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include "User.hpp"
#include "DatabaseHelper.hpp"

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

class UserCommand : public BaseCommand {
protected:
    User& user;
    DatabaseHelper& dbh;
public:
    UserCommand(std::string, User&, DatabaseHelper&);

    User& getUser() const;

    virtual void execute() = 0;
};

class RegisterCommand : public UserCommand {
public:
    RegisterCommand(User&, DatabaseHelper&);

    void execute();
};

class LoginCommand : public UserCommand {
public:
    LoginCommand(User&, DatabaseHelper&);

    void execute();
};

class TravelCommand : public UserCommand {
public:
    TravelCommand(User&, DatabaseHelper&);

    void execute();
};

class BrowseCommand : public UserCommand {
public:
    BrowseCommand(User&, DatabaseHelper&);

    void execute();
};

class FriendCommand : public UserCommand {
public:
    FriendCommand(User&, DatabaseHelper&);

    void execute();
};

#endif
