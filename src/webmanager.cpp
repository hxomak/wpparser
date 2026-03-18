#include "../include/webmanager.h"

#include <iostream>
#include <ostream>

namespace {
    size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        static_cast<std::string *>(userp)->append(static_cast<char *>(contents), size * nmemb);
        return size * nmemb;
    }
}

std::string GetHtmlCode(const std::string &_url, CURL *_page) {
    std::string htmlCode;
    try {
        curl_easy_setopt(_page, CURLOPT_URL, _url.c_str());
        curl_easy_setopt(_page, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(_page, CURLOPT_WRITEDATA, &htmlCode);
        curl_easy_setopt(_page, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(_page, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36");

        curl_easy_setopt(_page, CURLOPT_CAINFO, "C:\\_Download\\cacert.pem");
        curl_easy_setopt(_page, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(_page, CURLOPT_SSL_VERIFYHOST, 2L);

        const auto result = curl_easy_perform(_page);
        if (result != CURLE_OK) {
            throw std::runtime_error(curl_easy_strerror(result));
        }

        return htmlCode;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return {};
    }
}
