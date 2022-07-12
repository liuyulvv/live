/**
 * @file address.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-11
 */

#pragma once

#include <netinet/in.h>
#include <string>

namespace net {

class Address {
public:
    Address();
    Address(const std::string &ip, const unsigned &port);
    ~Address() = default;

public:
    void Update();
    const std::string& GetIP() const;
    unsigned GetPort() const;

public:
    sockaddr_in sockaddr;
    socklen_t sockaddr_len;

private:
    std::string ip_;
    unsigned port_;
};

}  // namespace net