#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    /* Would be better to identify with id insead of the username
        but it's not a real database */
    std::string username;
    std::string passwordHash;
    std::string email;
    bool loggedIn = false;

    std::vector<std::string> friends;
public:
    User();
    User(std::string, std::string, std::string);

    std::string getUsername() const;
    std::string getPasswordHash() const;
    std::string getEmail() const;
    std::vector<std::string> getFriends() const;
    bool getLoggedIn() const;

    void setLoggedIn(bool);

    void addFriend(std::string);
    bool checkCredentials(std::string, std::string);

    friend std::ostream& operator<<(std::ostream&, const User&);
    friend std::istream& operator>>(std::istream&, User&);
};

#endif
