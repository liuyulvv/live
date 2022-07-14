/**
 * @file tcpserver.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#include "tcpserver.hpp"
#include "util.hpp"

namespace net
{

TCPServer::TCPServer(const SEventloop &eventloop, const std::string &ip, const unsigned &port) {
    eventloop_ = eventloop;
    acceptor_ = std::make_shared<TCPAcceptor>(eventloop_, ip, port);
    threadpool_ = std::make_shared<util::ThreadPool>();
    acceptor_->SetNewConnectionCallback(std::bind(&TCPServer::HandleNewConnection, this, std::placeholders::_1, std::placeholders::_2));
    threadpoolSize_ = std::thread::hardware_concurrency();
    for (int i = 0; i < threadpoolSize_; ++i) {
        subEventloops_.push_back(std::make_shared<event::Eventloop>());
    }
    for (int i = 0; i < threadpoolSize_; ++i) {
        auto subLoop = std::bind(&event::Eventloop::Loop, subEventloops_[i]);
        threadpool_->Add(subLoop);
    }
}

void TCPServer::SetReadCallback(std::function<void(const STCPConnection &connection)> callback) {
    readCallback_ = callback;
}

void TCPServer::SetCloseCallback(std::function<void(const STCPConnection &connection)> callback) {
    closeCallback_ = callback;
}

void TCPServer::HandleRead(const STCPConnection &connection) {
    if (readCallback_ != nullptr) {
        readCallback_(connection);
    }
}

void TCPServer::HandleClose(const STCPConnection &connection) {
    if (closeCallback_ == nullptr) {
        connection_.Erase(connection->GetFd());
        return;
    }
    closeCallback_(connection);
}

void TCPServer::HandleNewConnection(int sockfd, const Address &address) {
    auto connection = std::make_shared<TCPConnection>(subEventloops_[sockfd % threadpoolSize_], sockfd);
    connection->SetReadCallback(std::bind(&TCPServer::HandleRead, this, std::placeholders::_1));
    connection->SetCloseCallback(std::bind(&TCPServer::HandleClose, this, std::placeholders::_1));
    connection->SetAddress(address);
    connection->EnableRead();
    connection_.Insert(sockfd, connection);
    util::Info("new client connnection, ip: ", connection->GetIp(), ", port: ", connection->GetPort());
}

} // namespace net