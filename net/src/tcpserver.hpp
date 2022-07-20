/**
 * @file tcpserver.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#pragma once

#include "address.hpp"
#include "eventloop.hpp"
#include "map.hpp"
#include "tcpacceptor.hpp"
#include "tcpconnection.hpp"
#include "threadpool.hpp"
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace net {

class TCPServer {
    public:
        using SEventloop = std::shared_ptr<event::Eventloop>;
        using STCPAcceptor = std::shared_ptr<TCPAcceptor>;
        using STCPConnection = std::shared_ptr<TCPConnection>;
        using SThreadPool = std::shared_ptr<util::ThreadPool>;

        TCPServer(const SEventloop& eventloop, const std::string& ip, unsigned port);
        virtual ~TCPServer() = default;

    protected:
        int threadpoolSize_ = 0;
        SEventloop eventloop_;
        SThreadPool threadpool_;
        STCPAcceptor acceptor_;
        std::vector<SEventloop> subEventloops_;
};

}  // namespace net