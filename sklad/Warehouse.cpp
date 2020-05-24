#include <vector>

#include "Warehouse.hpp"
#include "Item.hpp"
#include "Date.hpp"

Warehouse::Warehouse() {};

std::vector<Item> Warehouse::getItems() const {
    return this->items;
}

void Warehouse::setItems(std::vector<Item> items) {
    this->items = items;
}

void Warehouse::addItem(Item item) {
    this->items.push_back(item);
}

void Warehouse::clean() {
    Date currentDate = Date::getCurrentDate();

    for (auto it = this->items.begin(); it != items.end(); it++) {
        if ((*it).getExpirationDate() < currentDate) {
            this->items.erase(it--);
        }
    }
}
