#ifndef DOWNLOAD_HPP
#define DOWNLOAD_HPP

int connectSocket(const char* url);
bool downloadFile(const char* url, const char* dest);

#endif
