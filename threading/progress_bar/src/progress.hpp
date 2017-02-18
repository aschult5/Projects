#ifndef PROGRESS_HPP
#define PROGRESS_HPP

#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>

template<typename T>
class ProgressBar
{
public:
   ProgressBar(T total) : goal(total)
   {
      sum.store(static_cast<T>(0));
   }

   // Returns whether we finished properly
   bool displayUntilDone(std::chrono::milliseconds ms) const {
      // TODO register for timer
      while (sum.load() < goal)
      {
         displayOnce();
         std::this_thread::sleep_for(ms);
      }
      return sum.load() == goal;
   }

   // Returns % done as type T
   T displayOnce() const {
      T ret = (sum.load() * static_cast<T>(100)) / goal;
      std::cout << ret << std::endl;
      return ret;
   }

   void progress(T units) {
      sum += units;
   }

private:
   std::atomic<T> sum;
   const T goal;
protected:
};

#endif
