#include "inventory.hpp"
#include <iostream>

using namespace std;

double Inventory::value() const {
   double sum=0.0;
   for (auto it=database.begin(); it!=database.end(); it++)
   {
      sum += it->second.getPrice();
   }

   return sum;
}

double Inventory::priceLookup(unsigned int id) {
   if (database.count(id) == 0)
   {
      cout << "Product doesn't exist" << endl;
      return -1.0;
   }
   return database.at(id).getPrice();
}

bool Inventory::sell(unsigned int id, unsigned int quantity) {
   if (database.count(id) == 0)
   {
      cout << "Product doesn't exist" << endl;
      return false;
   }
   return database.at(id).reduceQuantity(quantity);
}
