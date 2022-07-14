/**
 * @file poller.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-12
 */

#pragma once

#include <vector>
#ifdef __APPLE__
#include <sys/event.h>
#endif

#include "tcpchannel.hpp"

namespace event
{

class Poller {
public:
    Poller();
    ~Poller();

public:
    int GetPollerFd() const;
    void UpdateTCPChannel(net::TCPChannel *channel);
    void RemoveTCPChannel(net::TCPChannel *channel);
    std::vector<net::TCPChannel *> Poll();

private:
    int fd_ = -1;
#ifdef __APPLE__
    struct kevent *event_ = nullptr;
#endif

};

} // namespace event
