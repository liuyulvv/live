/**
 * @file tcpchannel.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-12
 */

#pragma once

#include <functional>
#include <memory>

namespace event
{
    class Eventloop;
} // namespace event

namespace net
{

class TCPChannel : public std::enable_shared_from_this<TCPChannel>{
public:
    using SEventloop = std::shared_ptr<event::Eventloop>;

public:
    TCPChannel(std::shared_ptr<event::Eventloop> eventloop, int fd, bool et = false);
    ~TCPChannel() = default;

public:
    void HandleEvent();
    void EnableRead();
    void EnableNonBlock();
    int GetFd() const;
    int GetListenEvents() const;
    int GetReadyEvents() const;
    void SetReadyEvents(int readyEvents);
    bool IsInPoller() const;
    bool IsEt() const;

    void SetReadCallback(const std::function<void()> &readCallback);

private:
    SEventloop eventloop_;
    int fd_ = -1;
    int listenEvents_ = 0;
    int readyEvents_ = 0;
    bool et_ = false;
    bool isInPoller_ = false;

    std::function<void()> readCallback_;
};

} // namespace net
