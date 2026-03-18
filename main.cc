#include <iostream>
#include <string>

#include "include/WPParser.h"

using namespace std;

int main() {
    cout << "This is test programm" << std::endl;

    CURL_INIT;

    auto page = curl_easy_init();

    const auto htmlCode = GetHtmlCode("https://codeforces.com/profile/hxomak", page);

    Tag tag;
    tag.MakeRoot(htmlCode);

    auto found = tag.FindTag(GUMBO_TAG_DIV, "class", "second-level-menu");

    cout << found.GetHtmlView();

    GUMBO_CLEAN(tag);
    CURL_CLEAN;

    return 0;
}
