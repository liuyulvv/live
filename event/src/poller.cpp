/**
 * @file poller.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-12
 */

#include "poller.hpp"
#ifdef __APPLE__
#include <sys/event.h>
#endif
#include <unistd.h>

namespace event {

namespace {
const int MAX_EVENT = 1024;
}

Poller::Poller() {
#ifdef __APPLE__
    fd_ = kqueue();
    assert(fd_ != -1);
    event_ = new struct kevent[MAX_EVENT];
    memset(event_, 0, sizeof(*event_) * MAX_EVENT);
#endif
}

Poller::~Poller() {
    close(fd_);
    fd_ = -1;
}

int Poller::GetPollerFd() const {
    return fd_;
}

void Poller::UpdateTCPChannel(net::TCPChannel* channel) const {
#ifdef __APPLE__
    struct kevent event[2];
    memset(&event, 0, sizeof(event));
    int n = 0;
    int op = EV_ADD | EV_ENABLE;
    if (channel->IsEt()) {
        op |= EV_CLEAR;
    }
    EV_SET(&event[n++], channel->GetFd(), channel->GetListenEvents(), op, 0, 0, channel);
    int ret = kevent(fd_, event, n, nullptr, 0, nullptr);
    assert(ret != -1);
#endif
}

void Poller::RemoveTCPChannel(net::TCPChannel* channel) const {
#ifdef __APPLE__
    struct kevent event[2];
    int n = 0;
    EV_SET(&event[n++], channel->GetFd(), EVFILT_READ, EV_DELETE, 0, 0, channel);
    int ret = kevent(fd_, event, n, nullptr, 0, nullptr);
    assert(ret != -1);
#endif
}

std::vector<net::TCPChannel*> Poller::Poll() {
    std::vector<net::TCPChannel*> activeChannels;
#ifdef __APPLE__
    auto readyNums = kevent(fd_, nullptr, 0, event_, MAX_EVENT, nullptr);
    for (int i = 0; i < readyNums; ++i) {
        auto* activeChannel = reinterpret_cast<net::TCPChannel*>(event_[i].udata);
        activeChannel->SetReadyEvents(event_[i].filter);
        activeChannels.push_back(activeChannel);
    }
    return activeChannels;
#endif
}

}  // namespace event