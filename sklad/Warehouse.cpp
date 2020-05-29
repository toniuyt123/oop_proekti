#include <map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
 #include <sstream>

#include "Warehouse.hpp"
#include "Item.hpp"
#include "Date.hpp"

Warehouse::Warehouse() : spaces(100), spaceCapacity(10) {};
Warehouse::Warehouse(int spaces, int capacity) : spaces(spaces), spaceCapacity(spaceCapacity) {};

std::map<int, Item> Warehouse::getItems() const {
    return this->items;
}

void Warehouse::setItems(std::map<int, Item> items) {
    this->items = items;
}

void Warehouse::addItem(Item item) {
    int freeSpace = 1;

    for (auto& [space, it] : this->items) {
        if (space == freeSpace) {
            freeSpace++;
        }

        if (item.getName() == it.getName() && item.getExpirationDate() == it.getExpirationDate()) {
            int capacityLeft = this->spaceCapacity - it.getQuantity();

            if (capacityLeft >= item.getQuantity()) {
                it.updateQuantity(item.getQuantity());
                this->actions.push_back(WarehouseAction("add", item, Date::getCurrentDate(), space));

                return;
            } else {
                it.updateQuantity(capacityLeft);

                int intendedQuan = item.updateQuantity(-capacityLeft);
                item.setQuantity(capacityLeft);
                this->actions.push_back(WarehouseAction("add", item, Date::getCurrentDate(), space));
                
                item.setQuantity(intendedQuan);
            }
        }
    }

    int wholeQuantity = item.getQuantity();
    do {
        int quantity = std::min(this->spaceCapacity, item.getQuantity());

        item.setQuantity(quantity);
        wholeQuantity -= quantity;

        this->items.insert(std::pair<int, Item>(freeSpace, item));
        this->actions.push_back(WarehouseAction("add", item, Date::getCurrentDate(), freeSpace));
    } while (wholeQuantity > 0);
}

void Warehouse::removeItem(std::string name, int quantity) {
    std::vector<std::pair<int, Item>> items;

    for (auto it = this->items.begin(); it != this->items.end(); ++it) {
        if (it->second.getName() == name) {
            items.push_back((*it));
        }
    }

    int leftInStock = 0;
    for (auto& [space, item] : items) {
        leftInStock += item.getQuantity();
    }

    if (leftInStock < quantity) {
        std::string answer;
        
        do {
            std::cout << "There are " << leftInStock << " " << name << " left in stock. Remove all of them? (y/n)";
            std::cin >> answer;
        } while (answer != "y" && answer != "n");

        if (answer == "n") return;

        quantity = leftInStock;
    }

    sort(items.begin(), items.end(), [](const std::pair<int, Item>& a, const std::pair<int, Item>& b) -> bool { 
        return a.second.getExpirationDate() > b.second.getExpirationDate(); 
    });

    for (auto& [space, item] : items) {
        int oldQuantity = item.getQuantity();
        this->items[space].updateQuantity( - std::min(quantity, this->items[space].getQuantity()));
        quantity -= (oldQuantity - this->items[space].getQuantity());

        Item copy = item;
        copy.setQuantity(oldQuantity - this->items[space].getQuantity());
        this->actions.push_back(WarehouseAction("remove", copy, Date::getCurrentDate(), space));

        if (this->items[space].getQuantity() == 0) {
            this->items.erase(space);
        }
        if (quantity == 0) {
            break;
        }
    }
}

void Warehouse::clean() {
    Date currentDate = Date::getCurrentDate();

    for (auto it = this->items.begin(); it != items.end(); it++) {
        if (it->second.getExpirationDate() < currentDate) {
            this->actions.push_back(WarehouseAction("remove", it->second, Date::getCurrentDate(), it->first));

            it = this->items.erase(it);
        }
    }
}

void Warehouse::print() const {
    for (auto const& [space, item] : this->items) {
        int totalQuantity = 0;

        for (auto const& [key, value] : this->items) {
            if (value.getName() == item.getName()) {
                totalQuantity += value.getQuantity();
            }
        }
        std::cout << space << " -> ";
        std::cout << item.getName() << " " << item.getManufacturerName() << " Quanitity: " << item.getQuantity() << " Total in warehouse: " << totalQuantity << item.getMetric();
        std::cout << " Admissioned at: " << item.getAdmissionDate() << " Expires at: " << item.getExpirationDate() << ". Comment: " << item.getComment() << std::endl; 
    }
}

void Warehouse::toFile(std::ofstream& ofs) const {
    ofs << this->spaces << " " << this->spaceCapacity << std::endl;
    
    for (auto const& [space, item] : this->items) {
        ofs << space << " " << item << std::endl;
    }

    ofs << "|\n";
    
    for (auto const& action : this->actions) {
        ofs << action;
    }
}

void Warehouse::fromFile(std::ifstream& ifs) {
    ifs >> this->spaces >> this->spaceCapacity;

    std::string space;
    Item item;
    std::cout << "ee";
    while (ifs >> space) {
        std::cout << "Read: " << space;
        std::cout << (space == "|") << std::endl;
        if (space == "|") break;
        ifs >> item;

        this->items.insert(std::pair<int, Item>(std::stoi(space), item));
    }

    // get new line
    char c;
    ifs >> c;

    WarehouseAction action;
    std::string line;
    while(getline(ifs, line)) {
        std::istringstream stream;
        stream.str(line);
        stream >> action;
        this->actions.push_back(action);
    }
}

void Warehouse::log(Date start, Date end) const {
    std::vector<WarehouseAction> filtered;

    std::copy_if(this->actions.begin(), this->actions.end(), std::back_inserter(filtered), [&start, &end](WarehouseAction action) {
        return (action.getDate() > start && action.getDate() < end);
    });

    std::sort(filtered.begin(), filtered.end(), [](const WarehouseAction& a, const WarehouseAction& b) -> bool { 
        return a.getDate() > b.getDate(); 
    });

    for (auto& a : filtered) {
        std::cout << a;
    }
}

WarehouseAction::WarehouseAction() : action("null"), item(), date(), space(0) {};
WarehouseAction::WarehouseAction(std::string action, Item item, Date date, int space) : action(action), item(item), date(date), space(space) {};

Date WarehouseAction::getDate() const {
    return this->date;
}

void WarehouseAction::print() const {
    std::cout << this->date << " Action: " << this->action << " Space: " << this->space << " Item: " << this->item << std::endl;
}

std::ostream& operator<<(std::ostream& os, const WarehouseAction& action) {
    os << action.date << " " << action.action << " " << action.space << " " << action.item << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, WarehouseAction& action) {
    is >> action.date >> action.action >> action.space >> action.item;

    return is;
}