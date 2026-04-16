#include "crawler.h"
#include <iostream>

int main() {
    DoubanCrawler crawler;
    if (crawler.fetchTopList()) {
        std::cout << "Crawler framework run success.\n";
    } else {
        std::cout << "Crawler failed.\n";
    }
    return 0;
}
