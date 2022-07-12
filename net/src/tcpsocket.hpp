/**
 * @file tcpsocket.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-12
 */

#pragma once

#include "address.hpp"

namespace net
{

class TCPSocket {
public:
    TCPSocket();
    explicit TCPSocket(int sockfd);
    ~TCPSocket();

public:
    int GetSockfd() const;
    void Bind(const Address &address);
    void Listen();
    void Connect(Address &address);
    int Accept(Address &address);
    void SetNonBlock();

private:
    int sockfd_ = -1;
};
    
} // namespace net
