#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <unordered_map>
#include <string>
#include "product.hpp"

class Inventory {
public:
   unsigned int size() { return numProducts; }
   double getValue() const;
   double priceLookup(unsigned int id);
   bool sell(unsigned int id, unsigned int quantity);
private:
   unsigned int numProducts;
   std::unordered_map<unsigned int,Product> database;
protected:
};

#endif
