#include <gtest/gtest.h>
#include "sequence.hpp"
#include <vector>

//
// single-thread testing
//
TEST(SequenceTest, EmptyVector) {
   std::vector<int> vec;
   ASSERT_EQ(0, longestConsecutiveSequence(vec));
}

TEST(SequenceTest, SingleElement) {
   std::vector<int> vec {1};
   ASSERT_EQ(1, longestConsecutiveSequence(vec));
}

TEST(SequenceTest, RepeatingInteger) {
   std::vector<int> vec {1, 1};
   ASSERT_EQ(2, longestConsecutiveSequence(vec));
}

TEST(SequenceTest, MultipleIntegers) {
   std::vector<int> vec {1, 1, 2, 2, 2};
   ASSERT_EQ(3, longestConsecutiveSequence(vec));
}

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
