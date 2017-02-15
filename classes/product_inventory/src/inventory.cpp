#include "inventory.hpp"
#include <iostream>

using namespace std;

double Inventory::value() const {
   double sum=0.0;
   for (auto it=database.begin(); it!=database.end(); it++)
   {
      sum += it->second.getPrice() * it->second.getQuantity();
   }

   return sum;
}

double Inventory::priceLookup(unsigned int id) const {
   if (database.count(id) == 0)
   {
      cout << "Product doesn't exist" << endl;
      return -1.0;
   }
   return database.at(id).getPrice();
}

void Inventory::stock(Product const& p) {
   if (database.count(p.getId()) == 0)
   {
      database.emplace(p.getId(), p);
   }
   else
   {
      Product& existing = database.at(p.getId());
      existing.increaseQuantity(p.getQuantity());
   }
}

unsigned int Inventory::checkStock(unsigned int id)
{
   if (database.count(id) == 0)
   {
      cout << "Product doesn't exist" << endl;
      return false;
   }
   return database.at(id).getQuantity();
}

bool Inventory::sell(unsigned int id, unsigned int quantity) {
   if (database.count(id) == 0)
   {
      cout << "Product doesn't exist" << endl;
      return false;
   }
   return database.at(id).reduceQuantity(quantity);
}
