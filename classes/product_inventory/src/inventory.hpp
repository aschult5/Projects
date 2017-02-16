#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <unordered_map>
#include <string>
#include "product.hpp"

class Inventory {
public:
   unsigned int size() const { return database.size(); }
   double value() const;
   double priceLookup(unsigned int id) const;
   void stock(Product const& p);
   unsigned int checkStock(unsigned int);
   bool sell(unsigned int id, unsigned int quantity);
private:
   std::unordered_map<unsigned int,Product> database;
protected:
};

#endif
