/**
 * @file tcpsocket.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-12
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "tcpsocket.hpp"

namespace net
{

namespace {
    const int MAX_LISTEN = 1024;
}
    
TCPSocket::TCPSocket() {
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd_ != -1);
}

TCPSocket::TCPSocket(int sockfd) {
    sockfd_ = sockfd;
    assert(sockfd_ != -1);
}

TCPSocket::~TCPSocket() {
    close(sockfd_);
    sockfd_ = -1;
}

int TCPSocket::GetSockfd() const {
    assert(sockfd_ != -1);
    return sockfd_;
}

void TCPSocket::Bind(const Address &address) {
    assert(sockfd_ != -1);
    assert(bind(sockfd_, reinterpret_cast<const sockaddr*>(&address.sockaddr), address.sockaddr_len) != -1);
}

void TCPSocket::Listen() {
    assert(sockfd_ != -1);
    assert(listen(sockfd_, MAX_LISTEN) != -1);
}

void TCPSocket::Connect(Address &address) {
    assert(sockfd_ != -1);
    assert(connect(sockfd_, reinterpret_cast<sockaddr*>(&address.sockaddr), address.sockaddr_len) != -1);
}

int TCPSocket::Accept(Address &address) {
    assert(sockfd_ != -1);
    auto ret = accept(sockfd_, reinterpret_cast<sockaddr*>(&address.sockaddr), &address.sockaddr_len);
    assert(ret != -1);
    address.Update();
    return ret;
}

void TCPSocket::SetNonBlock() {
    assert(sockfd_ != -1);
    assert(fcntl(sockfd_, F_SETFL, fcntl(sockfd_, F_GETFL) | O_NONBLOCK) == -1);
}

} // namespace net