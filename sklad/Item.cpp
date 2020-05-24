#include <iostream>

#include "Item.hpp"


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


void Item::print() {
    std::cout << this->manufacturerName << " " << this->name << " " << this->quantity << this->metric;
    std::cout << " Admissioned at: " << this->admissionDate << " Expires at: " << this->expirationDate << ". Comment: " << this->comment; 
}

void Item::updateQuantity(int amount) {
    this->quantity += amount;
}
