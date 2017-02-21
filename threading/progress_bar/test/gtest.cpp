#include "progress.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace Bar {

//
// single-thread testing
//
TEST(ProgressBarTest, IsInitiallyZero) {
   ProgressBar<unsigned int> bar (100);
   ASSERT_EQ(0, bar.displayOnce());
}

TEST(ProgressBarTest, ProgressMethod) {
   ProgressBar<unsigned int> bar (100);
   bar.progress(25);
   ASSERT_EQ(25, bar.displayOnce());
}

TEST(ProgressBarTest, WeirdGoal) {
   ProgressBar<unsigned int> bar (250);
   bar.progress(25);
   ASSERT_EQ(10, bar.displayOnce());
}

//
// multi-thread testing
//
#include <thread>
TEST(ProgressBarTest, NotInfinite) {
   ProgressBar<unsigned int> bar (100);
   std::thread th(&ProgressBar<unsigned int>::displayUntilDone, &bar);
   for (auto i=0; i<100; ++i)
      bar.progress(1);
   th.join();
   ASSERT_EQ(100, bar.displayOnce());
}

} // Bar namespace

#include "download.hpp"
TEST(DownloadTest, ConnectToGoogle) {
   std::pair<int, const char*> connection = connectSocket("www.google.com");
   EXPECT_GE(connection.first, 0);
   close(connection.first);
}


int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
