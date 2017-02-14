#ifndef PRODUCT_HPP
#define PRODUCT_HPP

class Product
{
public:
   Product(unsigned int _id, float _price, unsigned int _quantity=0)
      :id(_id),
      price(_price),
      quantity(_quantity)
   { }

   float getPrice() const { return price; }
   unsigned int getQuantity() const { return quantity; }

private:
   unsigned int id;
   float price;
   unsigned int quantity;
protected:
};

#endif
