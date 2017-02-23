#include "sequence.hpp"
#include <iostream>
#include <climits>

// Return the last instance of v in sorted
unsigned int findFirstGreater(std::vector<int> const& sorted,
                       int v, unsigned int l, unsigned int r)
{
   using namespace std;
   if (r > sorted.size() || l > r)
   {
      cout << "Bad params" << endl;
      return 0;
   }

   unsigned int i;
   while (l != r)
   {
      i = (l + r)/2;

      if (sorted[i] <= v)
      {
         // Right
         l = i+1;
      }
      else if (sorted[i] > v)
      {
         // Left
         r = i;
      }
   }

   if (sorted[l] == v)
      return l+1;
   else
      return l;
}

int longestConsecutiveSequence(std::vector<int> const& sorted)
{
   unsigned int max=0;

   unsigned int i=0;
   while (i < sorted.size())
   {
      unsigned int j = findFirstGreater(sorted, sorted[i], i, sorted.size()-1);
      if (j - i > max)
         max = j - i;
      i = j;
   }

   return max;
}
