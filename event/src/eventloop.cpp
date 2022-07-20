/**
 * @file eventloop.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-12
 */

#include "eventloop.hpp"

namespace event {

Eventloop::Eventloop() {
    poller_ = std::make_shared<Poller>();
}

void Eventloop::Loop() {
    while (true) {
        auto activeChannels = poller_->Poll();
        for (auto& channel : activeChannels) {
            channel->HandleEvent();
        }
    }
}

void Eventloop::UpdateChannel(const STCPChannel& channel) {
    poller_->UpdateTCPChannel(channel.get());
}

void Eventloop::RemoveChannel(const STCPChannel& channel) {
    poller_->RemoveTCPChannel(channel.get());
}

}  // namespace event