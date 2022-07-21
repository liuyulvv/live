/**
 * @file rtmpconnection.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#pragma once

#include "address.hpp"
#include "buffer.hpp"
#include "eventloop.hpp"
#include "tcpchannel.hpp"
#include "tcpconnection.hpp"
#include "tcpsocket.hpp"
#include <functional>
#include <memory>
#include <string>

namespace rtmp {

enum class RTMPStatus {
    UNINITIALIZED,
    ACK_SEND,
    HANDSHAKE_DOWN
};

class RTMPConnection final : public net::TCPConnection {
    public:
        using SEventloop = std::shared_ptr<event::Eventloop>;

        RTMPConnection(const SEventloop& eventloop, int fd, bool et = false);
        ~RTMPConnection() override = default;

        RTMPStatus GetStatus() const;
        void SetStatus(const RTMPStatus& status);
        void OnStreamData();

    private:
        RTMPStatus status_ = RTMPStatus::UNINITIALIZED;
};

}  // namespace rtmp