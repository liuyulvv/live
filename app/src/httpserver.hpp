/**
 * @file httpserver.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#pragma once

#include "eventloop.hpp"
#include "tcpconnection.hpp"
#include "tcpserver.hpp"
#include <memory>

namespace app {

class HTTPServer : public net::TCPServer {
    public:
        using SEventloop = std::shared_ptr<event::Eventloop>;
        using STCPConnection = std::shared_ptr<net::TCPConnection>;

        HTTPServer(const SEventloop& eventloop, const std::string& ip, const unsigned& port);
        ~HTTPServer() override = default;

    private:
        util::Map<int, STCPConnection> connection_;
};

}  // namespace app