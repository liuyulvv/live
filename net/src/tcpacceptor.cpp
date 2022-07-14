/**
 * @file tcpacceptor.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#include "tcpacceptor.hpp"

namespace net
{

TCPAcceptor::TCPAcceptor(const SEventloop &eventloop, const std::string &ip, unsigned port) {
    eventloop_ = eventloop;
    Address address(ip, port);
    socket_ = std::make_shared<TCPSocket>();
    socket_->Bind(address);
    socket_->Listen();
    channel_ = std::make_shared<TCPChannel>(eventloop_, socket_->GetSockfd());
    channel_->SetReadCallback([this] { this->HandelRead(); });
    channel_->EnableRead();
}

void TCPAcceptor::SetNewConnectionCallback(const std::function<void(int sockfd, const Address &address)> &callback) {
    newConnectionCallback_ = callback;
}


void TCPAcceptor::HandelRead() {
    Address address;
    auto sockfd = socket_->Accept(address);
    assert(sockfd != -1 && newConnectionCallback_ != nullptr);
    newConnectionCallback_(sockfd, address);
}

} // namespace net