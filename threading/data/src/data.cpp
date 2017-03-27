#include <cstdlib>
#include <future>
#include <array>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

static const array<unsigned, 5> d1{2, 4, 8, 16, 32};
static const array<unsigned, 5> d2{20, 40, 80, 160, 320};
static const array<unsigned, 5> d3{200, 400, 800, 1600, 3200};
static const array<unsigned, 5> d4{2000, 4000, 8000, 16000, 32000};
static const array<unsigned, 5> d5{20000, 40000, 80000, 160000, 320000};

template<typename T>
T getData(const array<T, 5>& d)
{
   return accumulate(d.begin(), d.end(), 0);
}

int main(int argc, char* argv[])
{
   if (argc != 2)
      return 1;

   unsigned long long sum=0;
   vector<future<unsigned>> data;
   data.push_back(async(getData<decltype(d5)::value_type>,d5));
   data.push_back(async(getData<decltype(d4)::value_type>,d4));
   data.push_back(async(getData<decltype(d3)::value_type>,d3));
   data.push_back(async(getData<decltype(d2)::value_type>,d2));
   data.push_back(async(getData<decltype(d1)::value_type>,d1));

   while (sum < strtoul(argv[1], nullptr, 0) && !data.empty())
   {
      sum += data.back().get();
      data.pop_back();

      cout << "sum is " << sum << endl;
   }

   return 0;
}