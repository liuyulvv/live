/**
 * @file tcpacceptor.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#pragma once

#include <functional>
#include <memory>
#include <string>

#include "address.hpp"
#include "eventloop.hpp"
#include "tcpchannel.hpp"
#include "tcpsocket.hpp"

namespace net
{
    
class TCPAcceptor {
public:
    using SEventloop = std::shared_ptr<event::Eventloop>;
    using STCPSocket = std::shared_ptr<TCPSocket>;
    using STCPChannel = std::shared_ptr<TCPChannel>;

public:
    TCPAcceptor(const SEventloop &eventloop, const std::string &ip, unsigned port);
    ~TCPAcceptor() = default;

public:
    void SetNewConnectionCallback(const std::function<void(int sockfd, const Address &address)> &callback);

private:
    void HandelRead();

private:
    SEventloop eventloop_;
    STCPSocket socket_;
    STCPChannel channel_;

    std::function<void(int sockfd, const Address &address)> newConnectionCallback_;
};

} // namespace net