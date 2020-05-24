#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include "Item.hpp"

class Warehouse {
private:
    std::vector<Item> items;
public:
    Warehouse();

    std::vector<Item> getItems() const;
    void setItems(std::vector<Item>);
    void addItem(Item);
    void clean();
};

class WarehouseAction {
private:
    Item item;
    Date date;
public:

};

#endif
