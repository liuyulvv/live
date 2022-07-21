/**
 * @file testhttp.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#include "eventloop.hpp"
#include "httpserver.hpp"
#include "util.hpp"

int main(int argc, char* argv[]) {
    assert(argc >= 1);
    util::GetLogger(argv[0]);
    try {
        auto event = std::make_shared<event::Eventloop>();
        auto httpServer = std::make_shared<app::HTTPServer>(event, "0.0.0.0", 8080);
        event->Loop();
    } catch (const std::exception& e) {
        util::Error(e.what());
    }
    return 0;
}