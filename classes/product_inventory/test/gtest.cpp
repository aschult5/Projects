#include "inventory.hpp"
#include <gtest/gtest.h>

namespace {

// The fixture for testing class Foo.
class InventoryTest : public ::testing::Test {
protected:
   // You can remove any or all of the following functions if its body
   // is empty.

   InventoryTest() {
      // You can do set-up work for each test here.
   }

   virtual ~InventoryTest() {
      // You can do clean-up work that doesn't throw exceptions here.
   }

   // If the constructor and destructor are not enough for setting up
   // and cleaning up each test, you can define the following methods:

   virtual void SetUp() {
      // Code here will be called immediately after the constructor (right
      // before each test).
   }

   virtual void TearDown() {
      // Code here will be called immediately after each test (right
      // before the destructor).
   }

   // Objects declared here can be used by all tests in the test case for Foo.
   Inventory iut;
};


TEST_F(InventoryTest, IsInitiallyEmpty) {
   ASSERT_EQ(0, iut.size());
}

TEST_F(InventoryTest, StockMethod) {
   Product p(0, 1.0, 1);
   iut.stock(p);
   ASSERT_EQ(1, iut.size());
}

TEST_F(InventoryTest, PriceLookupMethod) {
   Product p(0, 1.0, 1);
   iut.stock(p);
   ASSERT_EQ(1.0, iut.priceLookup(p.getId()));
}

TEST_F(InventoryTest, SellMethod) {
   Product p(0, 1.0, 1);
   iut.stock(p);
   iut.sell(p.getId(), 1);
   ASSERT_EQ(0, iut.checkStock(p.getId()));
}

TEST_F(InventoryTest, ValueMethod) {
   Product p(0, 3.0, 3);
   Product p2(1, 1.0, 3);
   iut.stock(p);
   iut.stock(p2);
   ASSERT_EQ(12.0, iut.value());
}

} // namespace

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
