/**
 * @file address.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-11
 */

#include "address.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>

namespace net {

Address::Address() : sockaddr_len(sizeof(sockaddr)) {
    memset(&sockaddr, 0, sockaddr_len);
}

Address::Address(const std::string& ip, unsigned port) : Address() {
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
}

void Address::Update() {
    char* ip = new char[20];
    inet_ntop(AF_INET, &sockaddr.sin_addr, ip, 16);
    ip_ = std::string(ip);
    delete[] ip;
    port_ = ntohs(sockaddr.sin_port);
}

const std::string& Address::GetIP() const {
    return ip_;
}

unsigned Address::GetPort() const {
    return port_;
}

}  // namespace net