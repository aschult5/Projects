#ifndef PROGRESS_HPP
#define PROGRESS_HPP

#include <atomic>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

template<typename T>
class ProgressBar
{
public:
   ProgressBar(T total)
   : update(true),
     goal(total)
   {
      sum.store(static_cast<T>(0));
   }

   // Returns whether we finished properly
   bool displayUntilDone() {
      // TODO register for timer
      while (sum.load() < goal)
      {
         std::unique_lock<std::mutex> lk(m);
         cv.wait(lk, [this]{ return update; });

         displayOnce();
         update = false;

         lk.unlock();
      }
      displayOnce();
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
      {
         std::lock_guard<std::mutex> lk(m);
         update = true;
      }
      cv.notify_one();
   }

private:
   std::condition_variable cv;
   std::mutex m;
   bool update;

   std::atomic<T> sum;
   const T goal;
protected:
};

#endif
