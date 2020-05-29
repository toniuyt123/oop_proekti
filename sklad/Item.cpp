#include <iostream>
#include <sstream>

#include "Item.hpp"

Item::Item()
    : name(""), expirationDate(), admissionDate(), manufacturerName(""), metric(kg), quantity(0), comment("") {};

Item::Item(std::string name, Date expirationDate, Date admissionDate, std::string manufacturerName, Metric metric, int quantity, std::string comment)
    : name(name), expirationDate(expirationDate), admissionDate(admissionDate), manufacturerName(manufacturerName), metric(metric), quantity(quantity), comment(comment) {};

Item::Item(std::string name, Date expirationDate, Date admissionDate, std::string manufacturerName, Metric metric, int quantity)
    : Item(name, expirationDate, admissionDate, manufacturerName, metric, quantity, "No comment") {};

Item::Item(std::string name, Date expirationDate, std::string manufacturerName, Metric metric, int quantity, std::string comment)
    : Item(name, expirationDate, Date::getCurrentDate(), manufacturerName, metric, quantity, comment) {};

Item::Item(std::string name, Date expirationDate, std::string manufacturerName, Metric metric, int quantity)
    : Item(name, expirationDate, Date::getCurrentDate(), manufacturerName, metric, quantity, "No comment") {};


std::string Item::getName() const {
    return this->name;
}
Date Item::getExpirationDate() const {
    return this->expirationDate;
}
Date Item::getAdmissionDate() const {
    return this->admissionDate;
}
std::string Item::getManufacturerName() const {
    return this->manufacturerName;
}
Metric Item::getMetric() const {
    return this->metric;
}
int Item::getQuantity() const {
    return this->quantity;
}
std::string Item::getComment() const {
    return this->comment;
}

void Item::setName(std::string name) {
    this->name = name;
}
void Item::setExpirationDate(Date expirationDate) {
    this->expirationDate = expirationDate;
}
void Item::setAdmissionDate(Date admissionDate) {
    this->admissionDate = admissionDate;
}
void Item::setManufacturerName(std::string manufacturerName) {
    this->manufacturerName = manufacturerName;
}
void Item::setMetric(Metric metric) {
    this->metric = metric;
}
void Item::setQuantity(int quantity) {
    this->quantity = quantity;
}
void Item::setComment(std::string comment) {
    this->comment = comment;
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << " " << item.expirationDate << " " << item.admissionDate << " " << item.manufacturerName << " " 
        << item.metric << " " << item.quantity << " " << item.comment;

    return os;
}

std::istream& operator>>(std::istream& input, Item& item) { 
    input >> item.name >> item.expirationDate >> item.admissionDate >> item.manufacturerName 
        >> item.metric >> item.quantity >> item.comment;

    return input;            
}

std::istream& operator>>(std::istream& is, Metric& m) {
    std::string tmp;

    if (is >> tmp) {
        if (tmp == "kg") {
            m = kg;
        } else if (tmp == "l") {
            m = l;
        } else {
            throw "Invalid metric";
        }   
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Metric& m) {
    std::string tmp;

    switch (m) {
        case kg:  tmp = "kg"; break; 
        case l: tmp = "l"; break; 
        default: tmp = "?";
    }

    return os << tmp;
} 

void Item::print() {
    std::cout << this->manufacturerName << " " << this->name << " " << this->quantity << this->metric;
    std::cout << " Admissioned at: " << this->admissionDate << " Expires at: " << this->expirationDate << ". Comment: " << this->comment; 
}

int Item::updateQuantity(int amount) {
    this->quantity += amount;

    return this->quantity;
}
