/**
 * @file testhttp.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#include "util.hpp"
#include "eventloop.hpp"
#include "httpserver.hpp"

int main(int argc, char *argv[]) {
    util::GetLogger(argv[0]);
    auto event = std::make_shared<event::Eventloop>();
    auto httpServer = std::make_shared<app::HTTPServer>(event, "0.0.0.0", 8000);
    event->Loop();
    return 0;
} 