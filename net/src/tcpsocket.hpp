/**
 * @file tcpsocket.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-12
 */

#pragma once

#include "address.hpp"

namespace net {

class TCPSocket {
    public:
        TCPSocket();
        explicit TCPSocket(int sockfd);
        ~TCPSocket();

        [[nodiscard]] int GetSockfd() const;
        void Bind(const Address& address) const;
        void Listen() const;
        void Connect(Address& address) const;
        [[nodiscard]] int Accept(Address& address) const;
        void SetNonBlock() const;

    private:
        int sockfd_ = -1;
};

}  // namespace net