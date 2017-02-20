#include "progress.hpp"
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>


// Returns fd and filename
std::pair<int, const char*> connectSocket(const char* host)
{
   struct hostent *h;
   struct sockaddr_in dest;
   int sockfd;
   char on=1;

   if (host == NULL)
      exit(1);

   h = gethostbyname(host);
   if (h == NULL)
      exit(2);

   // create and open socket connection
   sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (sockfd == -1)
      exit(3);
   setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));

   dest.sin_family = AF_INET;
   dest.sin_port = htons(80);
   memcpy(&dest.sin_addr.s_addr, h->h_addr, h->h_length);

   if (connect(sockfd, (struct sockaddr *)&dest, sizeof(struct sockaddr)) == -1)
      exit(4);

   return std::pair<int, const char*>(sockfd, h->h_name);
}

bool downloadFile(const char* url, const char* destFile)
{
   // Extract host and file from URL
   char urlcpy[255];
   strncpy(urlcpy, url, 255);
   const char* host = strtok(urlcpy, "/");
   const char* file = strtok(NULL, "\0");
   FILE* destfp;

   // Connect to host
   std::pair<int, const char*> connection = connectSocket(host);
   int sockfd = connection.first;
   host = connection.second;

   // Print connection info
   std::cout << sockfd << std::endl;
   std::cout << (const char*)(host==NULL ? "":host) << std::endl;
   std::cout << (const char*)(file==NULL ? "":file) << std::endl;

   // Open destFile for writing
   if (destFile == nullptr)
      destfp = stdout;
   else
      destfp = fopen(destFile, "w");

   // Download file
   char req[255] = "GET /\r\n";
   if (file != NULL)
      strncat(req, file, 255-strlen("GET /\r\n")-1);
   char buffer[1024];
   memset(buffer, 0, sizeof(buffer));

   unsigned int n=0;
   do {
      n += write(sockfd, &req[n], strlen(req) - n);
   } while(n < strlen(req));

   while (read(sockfd, buffer, sizeof(buffer)-1) > 0)
   {
      fprintf(destfp, "%s", buffer);
      memset(buffer, 0, sizeof(buffer));
   }
   if (destfp != stdout)
   {
      fclose(destfp);
      destfp = nullptr;
   }

   shutdown(sockfd, SHUT_RDWR);
   close(sockfd);
   return true;
}
