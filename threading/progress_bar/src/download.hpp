#ifndef DOWNLOAD_HPP
#define DOWNLOAD_HPP

#include <utility>

std::pair<int, const char*> connectSocket(const char* url);
bool downloadFile(const char* url, const char* dest);

#endif
