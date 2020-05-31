#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "Travel.hpp"

Travel::Travel() {}
Travel::Travel(std::string destination, Date from, Date to, float grade, std::string comment, std::vector<std::string> photos)
    : destination(destination), from(from), to(to), grade(grade), comment(comment), photos(photos) {
    
    if (from > to) {
        throw "Inavlid dates. Start date should be smaller than end date";
    }

    for (auto& photo : photos) {
        std::string::size_type i;

        for (i = 0; i < photo.size(); i++) {
            if (photo[i] == '.') {
                break;
            } else if ((photo[i] < 'a' || photo[i] > 'z') && (photo[i] < 'A' || photo[i] > 'Z') && (photo[i] != '_')) {
                throw "Invalid photo name";
            }
        }

        std::string extension = photo.substr(i + 1);

        if (extension != "jpeg" && extension != "png") {
            throw "Invalid photo name";
        }
    }

    if (grade < 1 || grade > 5) {
        throw "Invalid grade";
    }
}


std::string Travel::getDestination() const {
    return this->destination;
}

Date Travel::getStartDate() const {
    return this->from;
}

Date Travel::getEndDate() const {
    return this->to;
}

float Travel::getGrade() const {
    return this->grade;
}

std::string Travel::getComment() const {
    return this->comment;
}

std::vector<std::string> Travel::getPhotos() const {
    return this->photos;
}


void Travel::setDestination(std::string destination) {
    this->destination = destination;
}

void Travel::setStartDate(Date from) {
    this->from = from;
}

void Travel::setEndDate(Date to) {
    this->to = to;
}

void Travel::setGrade(float grade) {
    this->grade = grade;
}

void Travel::setComment(std::string comment) {
    this->comment = comment;
}

void Travel::setPhotos(std::vector<std::string> photos) {
    this->photos = photos;
}

void Travel::addPhoto(std::string photo) {
    this->photos.push_back(photo);
}

void Travel::print() const {
    std::cout << this->destination << " from " << this->from << " to " << this->to << " Rated: "
        << this->grade << " \"" << this->comment << "\" Photos:";
    
    for (auto& photo : photos) {
        std::cout << " " << photo;
    }

    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Travel& travel) {
    os << travel.destination << "|" << travel.from << "|" << travel.to
        << "|" << travel.grade << "|" << travel.comment << "|";

    for (auto& photo : travel.photos) {
        os << " " << photo;
    }

    os << "|";

    return os;
}

std::istream& operator>>(std::istream& is, Travel& travel) {
    std::string token;
    std::istringstream stream;

    std::getline(is, travel.destination, '|');
    std::getline(is, token, '|');
    stream.str(token);
    stream >> travel.from;
    stream.clear();

    std::getline(is, token, '|');
    stream.str(token);
    stream >> travel.to;
    stream.clear();

    std::getline(is, token, '|');
    stream.str(token);
    stream >> travel.grade;
    stream.clear();
    
    std::getline(is, travel.comment, '|');

    std::getline(is, token, '|');
    stream.str(token);
    std::string photo;

    while(stream >> photo) {
        travel.addPhoto(photo);
    }

    return is;
}
