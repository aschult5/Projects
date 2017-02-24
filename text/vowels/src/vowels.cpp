#include "vowels.hpp"
#include <vector>

bool isVowel(char c)
{
   static std::vector<char> vowels { 'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u' };
   unsigned char l = 0, r = vowels.size()-1;

   while (l != r)
   {
      unsigned char i = (l+r)/2;
      if (c == vowels[i])
         return true;
      else if (c < vowels[i])
         r = i;
      else // c > vowels[i]
         l = i+1;
   }

   return c == vowels[l];
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
