#include "progress.hpp"
#include <iostream>
#include <fstream>
#include <thread>
#include <cstring>
#include <cmath>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>


// Returns socket fd and host
std::pair<int, const char*> connectSocket(const char* host)
{
   struct hostent *h;
   struct sockaddr_in dest;
   int sockfd;

   if (host == NULL)
      exit(1);

   h = gethostbyname(host);
   if (h == NULL)
      exit(2);

   // create and open socket connection
   sockfd = socket(PF_INET, SOCK_STREAM, 0);
   if (sockfd == -1)
      exit(3);

   dest.sin_family = AF_INET;
   dest.sin_port = htons(80);
   memcpy(&dest.sin_addr.s_addr, h->h_addr, h->h_length);

   if (connect(sockfd, (struct sockaddr *)&dest, sizeof(struct sockaddr)) == -1)
      exit(4);

   return std::pair<int, const char*>(sockfd, h->h_name);
}

// Tokenize header by CRLF, looking for Content-Length:
int getContentLength(char* header)
{
   const char* line = strtok(header, "\r\n");
   while (line != nullptr)
   {
      if ( strncmp(line, "Content-Length: ", strlen("Content-Length: ")) == 0 )
      {
         // Extract content-length
         return atoi(line+strlen("Content-Length: "));
      }
      line = strtok(NULL, "\r\n\0");
   }

   return -1;
}

bool downloadFile(const char* url, const char* destFile)
{
   // Extract host and file from URL
   char urlcpy[256];
   if (strncmp(url, "http://", strlen("http://")) == 0)
      strncpy(urlcpy, url+strlen("http://"), sizeof(urlcpy));
   else if (strncmp(url, "https://", strlen("https://")) == 0)
      strncpy(urlcpy, url+strlen("https://"), sizeof(urlcpy));
   else
      strncpy(urlcpy, url, sizeof(urlcpy));

   const char* host = strtok(urlcpy, "/");
   const char* file = strtok(NULL, "\0");

   // Connect to host
   std::pair<int, const char*> connection = connectSocket(host);
   int sockfd = connection.first;
   host = connection.second;

   // Form request
   char buf[4096];
   snprintf(buf, sizeof(buf), "GET /%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: HTMLGET 1.1\r\n\r\n", file==nullptr?"":file, host);

   // Send request
   unsigned int n=0;
   while(n < strlen(buf))
   {
      int sent = send(sockfd, &buf[n], strlen(buf) - n, 0);
      if (sent < 0)
      {
         std::cout << "Failed to send" << std::endl;
         n=0;
         break;
      }
      n += sent;
   }

   // Receive

   // // header (assume < sizeof buf)
   const char* suffix="\r\n\r\n";
   unsigned int total=0;
   int index=0;
   memset(buf, 0, sizeof(buf));

   while (sizeof(buf)-1 > total &&
          strncmp(buf + index, suffix, strlen(suffix)) != 0)
   {
      int rcvd = recv(sockfd, buf + total, sizeof(buf)-total-1, 0);
      if (rcvd < 0)
      {
         std::cout << "Failed to receive header" << std::endl;
         memset(buf, 0, sizeof(buf));
         break;
      }
      total += rcvd;

      index = strlen(buf)-strlen(suffix);
      if (index < 0)
         index = 0;
   }

   int length = getContentLength(buf);
   if (length < 0)
   {
      std::cout << "Failed to get Content-Length from header" << std::endl;
      std::cout << buf << std::endl;
   }

   // // file
   std::ofstream destfp (destFile);
   if (destfp.is_open())
   {

      ProgressBar<int> pb(length);
      std::thread th(&ProgressBar<int>::showProgressUntilDone, &pb);
      while (length > 0)
      {
         memset(buf, 0, sizeof(buf));
         int rcvd = recv(sockfd, buf, sizeof(buf)-1, 0);
         if (rcvd < 0)
            break;
         pb.makeProgress(rcvd);

         destfp << buf << std::flush;
         length -= rcvd;
      }
      th.join();

      destfp.close();
   }
   else
   {
      std::cout << "Failed to open file " << destFile << std::endl;
   }

   shutdown(sockfd, SHUT_RDWR);
   close(sockfd);
   return true;
}
