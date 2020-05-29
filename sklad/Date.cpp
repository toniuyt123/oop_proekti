#include <tuple>
#include <iostream>
#include <cassert>
#include <ctime>

#include "Date.hpp"

Date::Date() : year(1), month(1), day(1) {};
Date::Date(int year, int month, int day) : year(year), month(month), day(day) {
    if (year < 0) {
        throw "Invalid date";
    }
    if (month < 0 || month > 12) {
        throw "Invalid month";
    }

    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (this->isLeap()) {
        monthDays[1]++;
    }

    if (day < 0 || day > monthDays[month - 1]) {
        throw "Invalid day";
    }
}

bool Date::isLeap() {
    return ((this->year % 4 == 0) && (this->year % 100 != 0)) || (this->year % 400 == 0);
}

Date Date::getCurrentDate() {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    return Date(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.year << '-' << date.month << '-' << date.day;
    
    return os;
}

std::istream& operator>>(std::istream& input, Date& date) {
    std::string token;

    std::getline(input, token, '-');
    date.year = std::stoi(token);
    std::getline(input, token, '-');
    date.month = std::stoi(token);
    // std::getline(input, token, ' ');
    // date.day = std::stoi(token);
    input >> date.day;

    return input;            
}

bool operator== (Date const& lhs, Date const& rhs) {
    return lhs.year == rhs.year
        && lhs.month == rhs.month
        && lhs.day == rhs.day;
}

bool operator!= (Date const& lhs, Date const& rhs) {
    return ! (lhs == rhs);
}

bool operator> (Date const& lhs, Date const& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day)
        > std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator< (Date const& lhs, Date const& rhs) {
    return ( ! (lhs > rhs) ) && lhs != rhs;
}

bool operator>= (Date const& lhs, Date const& rhs) {
    return lhs > rhs || lhs == rhs;
}

bool operator<= (Date const& lhs, Date const& rhs) {
    return lhs < rhs || rhs == rhs;
}
