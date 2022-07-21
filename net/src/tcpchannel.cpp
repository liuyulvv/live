/**
 * @file tcpchannel.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-12
 */

#include "tcpchannel.hpp"
#include <fcntl.h>
#ifdef __APPLE__
#include <sys/event.h>
#endif
#ifdef __linux__
#include <sys/epoll.h>
#endif
#include "eventloop.hpp"
#include <cassert>

namespace net {

TCPChannel::TCPChannel(const SEventloop& eventloop, int fd, bool et) {
    eventloop_ = eventloop;
    fd_ = fd;
    et_ = et;
    assert(eventloop_ != nullptr && fd_ != -1);
}

void TCPChannel::HandleEvent() {
#ifdef __APPLE__
    if (readyEvents_ & EVFILT_READ) {
        readCallback_();
    }
#endif
#ifdef __linux__
    if (readyEvents_ & (EPOLLIN | EPOLLPRI)) {
        readCallback_();
    }
#endif
}

void TCPChannel::EnableRead() {
#ifdef __APPLE__
    listenEvents_ |= EVFILT_READ;
#endif
#ifdef __linux__
    listenEvents_ |= EPOLLIN | EPOLLPRI;
    if (et_) {
        listenEvents_ |= EPOLLET;
    }
#endif
    assert(eventloop_ != nullptr && fd_ != -1);
    eventloop_->UpdateChannel(shared_from_this());
    isInPoller_ = true;
}

void TCPChannel::EnableNonBlock() const {
    assert(fd_ != -1);
    fcntl(fd_, F_SETFL, fcntl(fd_, F_GETFL) | O_NONBLOCK);
}

int TCPChannel::GetFd() const {
    return fd_;
}

int TCPChannel::GetListenEvents() const {
    return listenEvents_;
}

int TCPChannel::GetReadyEvents() const {
    return readyEvents_;
}

void TCPChannel::SetReadyEvents(int readyEvents) {
    readyEvents_ = readyEvents;
}

bool TCPChannel::IsInPoller() const {
    return isInPoller_;
}

bool TCPChannel::IsEt() const {
    return et_;
}

void TCPChannel::SetReadCallback(const std::function<void()>& readCallback) {
    readCallback_ = readCallback;
}

}  // namespace net