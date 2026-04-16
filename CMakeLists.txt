cmake_minimum_required(VERSION 3.16)
project(douban_top_crawler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 依赖：libcurl（HTTP）、nlohmann/json（JSON解析）
find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})

add_executable(crawler
    src/main.cpp
    src/crawler.cpp
)

target_link_libraries(crawler ${CURL_LIBRARIES})
