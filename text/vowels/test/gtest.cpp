#include <gtest/gtest.h>
#include "vowels.hpp"
#include <string>

//
// single-thread testing
//
TEST(VowelTest, EmptyString) {
   std::string s = "";
   ASSERT_EQ(0, countVowels(s));
}

TEST(VowelTest, ShortString) {
   std::string s = "One two";
   ASSERT_EQ(3, countVowels(s));
}

TEST(VowelTest, NoVowels) {
   std::string s = "pffft";
   ASSERT_EQ(0, countVowels(s));
}

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
