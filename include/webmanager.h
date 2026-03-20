#ifndef WEBMANAGER_HEADER
#define WEBMANAGER_HEADER

#include <string>

#include <curl/curl.h>

#include "utils.h"

#define CURL_INIT \
curl_global_init(CURL_GLOBAL_ALL);

#define CURL_CLEAN \
curl_global_cleanup();

std::string GetHtmlCode(const std::string &_url, CURL *_page);

#endif //WEBMANAGER_HEADER
