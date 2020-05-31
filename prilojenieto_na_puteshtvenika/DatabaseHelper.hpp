#ifndef DATABASE_HELPER_H
#define DATABASE_HELPER_H

#include <string>
#include <fstream>

#include "User.hpp"
#include "Travel.hpp"

class DatabaseHelper {
private:
    std::fstream users;
protected:
    static std::string dbName;
public:
    DatabaseHelper();

    bool userExists(std::string);
    User getUser(std::string);
    void recordUser(const User&);
    void recordTravel(const User&, const Travel&);
    std::vector<Travel> getTravels(std::string);
    std::vector<User> getUsers(); 
    void addFriend(const User&, std::string);
}; 

#endif