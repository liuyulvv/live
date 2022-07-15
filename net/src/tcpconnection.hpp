/**
 * @file tcpconnection.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#pragma once

#include <functional>
#include <memory>
#include <string>

#include "address.hpp"
#include "buffer.hpp"
#include "eventloop.hpp"
#include "tcpchannel.hpp"
#include "tcpsocket.hpp"

namespace net
{

class TCPConnection : public std::enable_shared_from_this<TCPConnection>
{
public:
    using SEventloop = std::shared_ptr<event::Eventloop>;
    using STCPSocket = std::shared_ptr<TCPSocket>;
    using STCPChannel = std::shared_ptr<TCPChannel>;
    using SBuffer = std::shared_ptr<util::Buffer>;
    using STCPConnection = std::shared_ptr<TCPConnection>;

public:
    TCPConnection(const SEventloop &eventloop, int fd);
    virtual ~TCPConnection() = default;

public:
    int GetFd() const;
    void SetReadCallback(const std::function<void(const STCPConnection &connection)> &callback);
    void SetCloseCallback(const std::function<void(const STCPConnection &connection)> &callback);
    void EnableRead();
    std::vector<char> Recv();
    std::vector<char> Recv(int size);
    void Write(const std::string &content);
    void Write(char content);
    void Write(const std::vector<char> &content);
    void Write(int size, char content);
    void Send();
    void SetAddress(const Address &address);
    const std::string &GetIp() const;
    const unsigned GetPort() const;
    const STCPChannel &GetChannel() const;
    void HandleRead();
    void HandleClose(const STCPConnection &connection);
    bool HasContent() const;
    bool HasContent(int size) const;

protected:
    SEventloop eventloop_;
    STCPSocket socket_;
    STCPChannel channel_;
    SBuffer readBuffer_;
    SBuffer writeBuffer_;
    std::string ip_;
    unsigned port_;

    std::function<void(const STCPConnection &connection)> readCallback_;
    std::function<void(const STCPConnection &connection)> closeCallback_;
};

} // namespace net