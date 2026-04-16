#include "crawler.h"
#include <curl/curl.h>
#include <fstream>
#include <iostream>

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (...) {
        return 0;
    }
    return newLength;
}

std::string DoubanCrawler::httpGet(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        // 仅构建请求结构，不实现完整可用抓取
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

bool DoubanCrawler::parseHtml(const std::string& html) {
    // 仅占位，不实现解析
    return true;
}

void DoubanCrawler::saveResult(const std::string& data) {
    std::ofstream ofs("result.json");
    if (ofs) ofs << data;
}

bool DoubanCrawler::fetchTopList() {
    // 仅占位 URL，不保证可抓取
    std::string url = "https://movie.douban.com/top250";
    std::string html = httpGet(url);
    if (html.empty()) return false;

    parseHtml(html);
    saveResult("{}");
    return true;
}
