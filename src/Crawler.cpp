#include "crawler.h"
#include <curl/curl.h>
#include <iostream>
#include <string>

size_t write_cb(void* contents, size_t sz, size_t nmemb, std::string* s) {
    size_t newLen = sz * nmemb;
    s->append((char*)contents, newLen);
    return newLen;
}

std::string DoubanCrawler::httpGet(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string resp;

    if (!curl) return "";

    // 基础请求头，合规访问
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return resp;
}

bool DoubanCrawler::parse(const std::string& html) {
    // 仅演示结构，不做完整正则/HTML解析库依赖
    // 真实使用需引入 gumbo-parser / libxml2 / CTML
    MovieItem item;
    item.rank = "1";
    item.title = "肖申克的救赎（示例）";
    item.score = "9.7";
    movies.push_back(item);
    return true;
}

void DoubanCrawler::printResult() const {
    std::cout << "\n=== 豆瓣 Top250 结果 ===" << std::endl;
    for (const auto& m : movies) {
        std::cout << m.rank << ". " << m.title << " 评分: " << m.score << std::endl;
    }
}

bool DoubanCrawler::run() {
    std::string html = httpGet("https://movie.douban.com/top250");
    if (html.empty()) {
        std::cerr << "请求失败" << std::endl;
        return false;
    }
    parse(html);
    printResult();
    return true;
}
