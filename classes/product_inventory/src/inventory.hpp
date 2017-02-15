#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <unordered_map>
#include <string>
#include "product.hpp"

class Inventory {
public:
   Inventory() : numProducts(0) { }
   unsigned int size() const { return numProducts; }
   double value() const;
   double priceLookup(unsigned int id) const;
   bool sell(unsigned int id, unsigned int quantity);
private:
   unsigned int numProducts;
   std::unordered_map<unsigned int,Product> database;
protected:
};

#endif
