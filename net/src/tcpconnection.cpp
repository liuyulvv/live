/**
 * @file tcpconnection.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#include "tcpconnection.hpp"

#include <unistd.h>

namespace net
{

TCPConnection::TCPConnection(const SEventloop &eventloop, int fd) {
    eventloop_ = eventloop;
    socket_ = std::make_shared<TCPSocket>(fd);
    channel_ = std::make_shared<TCPChannel>(eventloop, fd, true);
    readBuffer_ = std::make_shared<util::Buffer>();
    writeBuffer_ = std::make_shared<util::Buffer>();
    channel_->SetReadCallback([this] { HandleRead(); });
    channel_->EnableNonBlock();
}

int TCPConnection::GetFd() const {
    return socket_->GetSockfd();
}

void TCPConnection::SetReadCallback(const std::function<void(const STCPConnection &connection)> &callback) {
    readCallback_ = callback;
}

void TCPConnection::SetCloseCallback(const std::function<void(const STCPConnection &connection)> &callback) {
    closeCallback_ = callback;
}

void TCPConnection::EnableRead() {
    channel_->EnableRead();
}

std::vector<char> TCPConnection::Recv() {
    return readBuffer_->GetContent();
}

std::vector<char> TCPConnection::Recv(int size) {
    return readBuffer_->GetContent(size);
}

void TCPConnection::Write(const std::string &content) {
    writeBuffer_->Push(content);
}

void TCPConnection::Write(char content) {
    writeBuffer_->Push(content);
}

void TCPConnection::Write(const std::vector<char> &content) {
    writeBuffer_->Push(content);
}

void TCPConnection::Write(int size, char content) {
    for (int i = 0; i < size; ++i)
    {
        writeBuffer_->Push(content);
    }
}

void TCPConnection::Send() {
    auto content = writeBuffer_->GetContent();
    write(socket_->GetSockfd(), &content[0], content.size());
}

void TCPConnection::SetAddress(const Address &address) {
    ip_ = address.GetIP();
    port_ = address.GetPort();
}

const std::string& TCPConnection::GetIp() const {
    return ip_;
}

const unsigned TCPConnection::GetPort() const {
    return port_;
}

const net::TCPConnection::STCPChannel& TCPConnection::GetChannel() const {
    return channel_;
}

void TCPConnection::HandleRead() {
    char buffer[65535];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        auto bytesRead = read(GetFd(), buffer, sizeof(buffer));
        if (bytesRead > 0) {
            readBuffer_->Push(buffer, bytesRead);
        }
        else if (bytesRead == -1 && errno == EINTR) {
            continue;
        }
        else if (bytesRead == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {
            readCallback_(shared_from_this());
            break;
        }
        else if (bytesRead == 0) {
            HandleClose(shared_from_this());
            break;
        }
    }
}

void TCPConnection::HandleClose(const STCPConnection &connection) {
    closeCallback_(connection);
    eventloop_->RemoveChannel(connection->GetChannel());
}

bool TCPConnection::HasContent() const {
    return !readBuffer_->Empty();
}

bool TCPConnection::HasContent(int size) const {
    return readBuffer_->Size() >= size;
}

} // namespace net