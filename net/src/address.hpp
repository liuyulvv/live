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
        Address(const std::string& ip, unsigned port);
        ~Address() = default;

        void Update();
        [[nodiscard]] const std::string& GetIP() const;
        [[nodiscard]] unsigned GetPort() const;

        sockaddr_in sockaddr;
        socklen_t sockaddr_len;

    private:
        std::string ip_;
        unsigned port_;
};

}  // namespace net