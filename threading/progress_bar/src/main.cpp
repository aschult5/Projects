#include "download.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
   if (argc != 3)
   {
      std::cout << "Usage: " << argv[0] << " <URL> <Output file>" << std::endl;
      return 1;
   }

   return downloadFile(argv[1], argv[2]) ? 0 : 1;
}
