#ifndef PROGRESS_HPP
#define PROGRESS_HPP

#include <string>
#include <iostream>
#include <atomic>
#include <mutex>
#include <condition_variable>

template<typename T>
class ProgressBar
{
public:
   ProgressBar(T total) : goal(total) {
      progress.store(0);
      sum.store(0);
   }

   // Returns whether we finished properly
   bool showProgressUntilDone() {
      while (sum.load() < goal)
      {
         std::unique_lock<std::mutex> lk(m);
         cv.wait(lk, [this]{ return progress.load() != 0; });

         auto copy = progress.load();
         progress.store(0);

         lk.unlock();

         showProgress(copy);
      }
      return sum.load() == goal;
   }

   inline T asPercent(T num) const {
      long long tmp1 = 100, tmp2 = goal;
      tmp1 *= num;
      return tmp1/tmp2;
   }

   T showProgress(T num) {
      auto tickSize = 10;
      T prev = asPercent(sum.load());
      prev -= (prev % tickSize);

      sum += num;
      T ret = asPercent(sum.load());

      std::string output((ret - prev) / tickSize, '=');
      std::cout << output << std::flush;

      return ret;
   }

   void makeProgress(T units){
      {
         std::lock_guard<std::mutex> lk(m);
         progress += units;
      }
      cv.notify_one();
   }

private:
   std::condition_variable cv;
   std::mutex m;

   std::atomic<T> progress;
   std::atomic<T> sum;
   const T goal;
protected:
};

#endif
