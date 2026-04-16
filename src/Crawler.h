#ifndef CRAWLER_H
#define CRAWLER_H

#include <string>

class DoubanCrawler {
public:
    bool fetchTopList();  // 抓取入口
private:
    std::string httpGet(const std::string& url);  // HTTP GET 骨架
    bool parseHtml(const std::string& html);      // 解析骨架
    void saveResult(const std::string& data);     // 保存结果
};

#endif
