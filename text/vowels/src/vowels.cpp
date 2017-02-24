#include "vowels.hpp"
#include <vector>

bool isVowel(char c)
{
   static std::vector<char> vowels { 'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U' };

   for (auto v : vowels)
   {
      if (v == c)
         return true;
   }

   return false;
}

unsigned int countVowels(std::string text)
{
   unsigned int cnt=0;
   for (auto c : text)
   {
      if (isVowel(c))
         ++cnt;
   }

   return cnt;
}
