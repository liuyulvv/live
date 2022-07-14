/**
 * @file httpserver.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#pragma once

#include <memory>

#include "eventloop.hpp"
#include "tcpserver.hpp"
#include "tcpconnection.hpp"

namespace app{

class HTTPServer final : public net::TCPServer {
public:
    using SEventloop = std::shared_ptr<event::Eventloop>;

public:
    HTTPServer(const SEventloop &eventloop, const std::string &ip, const unsigned &port);
    ~HTTPServer() = default;

private:
    void HandleRead(const STCPConnection &connection);
};

} // namespace app