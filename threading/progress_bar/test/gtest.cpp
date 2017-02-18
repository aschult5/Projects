#include "progress.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace {

// The fixture for testing class Foo.
class ProgressBarTest : public ::testing::Test {
protected:
   // You can remove any or all of the following functions if its body
   // is empty.

   ProgressBarTest() {
      // You can do set-up work for each test here.
   }

   virtual ~ProgressBarTest() {
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
   std::unique_ptr<ProgressBar<unsigned int>> pint;
};


TEST_F(ProgressBarTest, IsInitiallyZero) {
   pint = std::make_unique<ProgressBar<unsigned int>>(100);
   auto i=pint->displayOnce();
   ASSERT_EQ(0, i);
}

TEST_F(ProgressBarTest, ProgressMethod) {
   pint = std::make_unique<ProgressBar<unsigned int>>(100);
   pint->progress(25);
   auto i=pint->displayOnce();
   ASSERT_EQ(25, i);
}

} // namespace

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
