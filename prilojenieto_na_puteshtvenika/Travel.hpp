#ifndef TRAVEL_H
#define TRAVEL_H

#include <string>
#include <vector>

#include "Date.hpp"

class Travel {
private:
    std::string destination;
    Date from, to;
    float grade;
    std::string comment;
    std::vector<std::string> photos;
public:
    Travel();
    Travel(std::string, Date, Date, float, std::string, std::vector<std::string>);

    std::string getDestination() const;
    Date getStartDate() const;
    Date getEndDate() const;
    float getGrade() const;
    std::string getComment() const;
    std::vector<std::string> getPhotos() const;

    void setDestination(std::string);
    void setStartDate(Date);
    void setEndDate(Date);
    void setGrade(float);
    void setComment(std::string);
    void setPhotos(std::vector<std::string>);

    void print() const;
    void addPhoto(std::string);

    friend std::ostream& operator<<(std::ostream&, const Travel&);
    friend std::istream& operator>>(std::istream&, Travel&);
};

#endif
