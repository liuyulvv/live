/**
 * @file tcpchannel.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-12
 */

#pragma once

#include <functional>
#include <memory>

namespace event {
class Eventloop;
}  // namespace event

namespace net {

class TCPChannel : public std::enable_shared_from_this<TCPChannel> {
    public:
        using SEventloop = std::shared_ptr<event::Eventloop>;

        TCPChannel(const SEventloop& eventloop, int fd, bool et = false);
        ~TCPChannel() = default;

        void HandleEvent();
        void EnableRead();
        void EnableNonBlock() const;
        [[nodiscard]] int GetFd() const;
        [[nodiscard]] int GetListenEvents() const;
        [[nodiscard]] int GetReadyEvents() const;
        void SetReadyEvents(int readyEvents);
        [[nodiscard]] bool IsInPoller() const;
        [[nodiscard]] bool IsEt() const;

        void SetReadCallback(const std::function<void()>& readCallback);

    private:
        SEventloop eventloop_;
        int fd_ = -1;
        int listenEvents_ = 0;
        int readyEvents_ = 0;
        bool et_ = false;
        bool isInPoller_ = false;

        std::function<void()> readCallback_;
};

}  // namespace net