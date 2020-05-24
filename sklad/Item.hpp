#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Date.hpp"

enum Metric {kg, l};

class Item {
private:
    std::string name;
    Date expirationDate;
    Date admissionDate;
    std::string manufacturerName;
    Metric metric;
    int quantity;
    // place
    std::string comment;
public:
    Item(std::string, Date, Date, std::string, Metric, int, std::string);
    Item(std::string, Date, Date, std::string, Metric, int);
    Item(std::string, Date, std::string, Metric, int, std::string);
    Item(std::string, Date, std::string, Metric, int);

    std::string getName() const;
    Date getExpirationDate() const;
    Date getAdmissionDate() const;
    std::string getManufacturerName() const;
    Metric getMetric() const;
    int getQuantity() const;
    std::string getComment() const;

    void setName(std::string);
    void setExpirationDate(Date);
    void setAdmissionDate(Date);
    void setManufacturerName(std::string);
    void setMetric(Metric);
    void setQuantity(int);
    void setComment(std::string);

    void print();
    void updateQuantity(int);
};

#endif
