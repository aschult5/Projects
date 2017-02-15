#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <climits>

class Product
{
public:
   Product() = delete;
   Product(unsigned int _id, float _price, unsigned int _quantity=0)
      :id(_id),
      price(_price),
      quantity(_quantity)
   { }

   unsigned int getId() const {
      return id;
   }
   double getPrice() const { return price; }
   unsigned int getQuantity() const { return quantity; }
   bool reduceQuantity(unsigned int _quantity) {
      if (_quantity > quantity) return false;
      quantity -= _quantity;
      return true;
   }

   bool increaseQuantity(unsigned int _quantity) {
      if (UINT_MAX - _quantity > quantity) return false;
      quantity += _quantity;
      return true;
   }

private:
   unsigned int id;
   double price;
   unsigned int quantity;
protected:
};

#endif
