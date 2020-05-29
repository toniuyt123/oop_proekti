#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <map>
#include <vector>

#include "Item.hpp"

class WarehouseAction {
private:
    /* A big improvement would be not storing the whole item but just some id
        but it was too much work to redo. Besides the whole project would be better as an actual database in the first place */
    std::string action;
    Item item;
    Date date;
    int space;
public:
    WarehouseAction();
    WarehouseAction(std::string, Item, Date, int);

    Date getDate() const;

    void print() const;
    friend std::ostream& operator<<(std::ostream&, const WarehouseAction&);
    friend std::istream& operator>>(std::istream&, WarehouseAction&);
};

class Warehouse {
private:
    int spaces;
    int spaceCapacity;

    /* 
        Could be the same with vector but the map helps a bit with keeping it sorted
        and mainly it can later be upgrated easier to track products in a more complex way rather than just a number
    */
    std::map<int, Item> items;
    std::vector<WarehouseAction> actions;
public:
    Warehouse(int, int);
    Warehouse();

    std::map<int, Item> getItems() const;
    void setItems(std::map<int, Item>);
    void addItem(Item);
    void removeItem(std::string, int);
    void clean();

    void log(Date, Date) const;
    void print() const;
    void toFile(std::ofstream&) const;
    void fromFile(std::ifstream&);
};

#endif
