#include "progress.hpp"
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>

int connectSocket(const char* url)
{
   struct hostent *h;
   struct sockaddr_in dest;
   int sockfd, on=1;

   if (url == NULL)
      return -1;

   h = gethostbyname(url);
   if (h == NULL)
      return -2;

   // create and open socket connection (AF_INET, SOCK_STREAM, port=80)
   sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (sockfd == -1)
      return -3;
   setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (const char*)&on, sizeof(on));

   dest.sin_family = AF_INET;
   dest.sin_port = htons(80);
   bcopy(h->h_addr, &dest.sin_addr.s_addr, h->h_length);

   sockfd = connect(sockfd, (struct sockaddr *)&dest, sizeof(struct sockaddr));
   if (sockfd == -1)
      return -4;

   return sockfd;
}

bool downloadFile(const char* url, const char* dest)
{
   int fd = connectSocket(url);
   std::cout << fd << std::endl;

   close (fd);
   return true;
}
