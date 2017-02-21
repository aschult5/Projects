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
   ProgressBar(T total)
   : update(true),
     goal(total)
   {
      sum.store(static_cast<T>(0));
   }

   // Returns whether we finished properly
   bool displayUntilDone() {
      while (sum.load() < goal)
      {
         std::unique_lock<std::mutex> lk(m);
         cv.wait(lk, [this]{ return update; });

         displayOnce();
         update = false;

         lk.unlock();
      }
      displayOnce();
      std::cout << std::endl;
      return sum.load() == goal;
   }

   // Returns % done as type T
   T displayOnce() const {
      static T last = 0;
      T ret = (sum.load() * static_cast<T>(100)) / goal;

      std::cout.seekp(-10, std::ios_base::end);
      T prog = (ret - last)/10;
      while (prog-- > 0)
         std::cout << "=";
      last = ret - (ret%10);

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
