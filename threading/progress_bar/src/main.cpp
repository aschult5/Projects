#include "download.hpp"

int main(int argc, char* argv[])
{
   char* dest=nullptr;
   if (argc == 3)
      dest = argv[2];
   else if (argc != 2)
      return 1;

   if (downloadFile(argv[1], dest))
      return 0;

   return 1;
}
