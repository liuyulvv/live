/**
 * @file eventloop.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-12
 */

#pragma once

#include "poller.hpp"
#include "tcpchannel.hpp"
#include <memory>

namespace event {

class Eventloop {
    public:
        using SPoller = std::shared_ptr<Poller>;
        using STCPChannel = std::shared_ptr<net::TCPChannel>;

        Eventloop();
        ~Eventloop() = default;

        void Loop();
        void UpdateChannel(const STCPChannel& channel);
        void RemoveChannel(const STCPChannel& channel);

    private:
        SPoller poller_;
};

}  // namespace event