#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <map>
#include <string>
#include "product.hpp"

class Inventory {
public:
   unsigned int size() { return numProducts; }
   double getValue() const;
   Product const& lookup(unsigned int id);
private:
   unsigned int numProducts;
   std::map<unsigned int,Product> database;
protected:
};

#endif
