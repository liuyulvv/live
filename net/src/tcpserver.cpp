/**
 * @file tcpserver.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#include "tcpserver.hpp"

namespace net
{

TCPServer::TCPServer(const SEventloop &eventloop, const std::string &ip, unsigned port) {
    eventloop_ = eventloop;
    threadpool_ = std::make_shared<util::ThreadPool>();
    threadpoolSize_ = std::thread::hardware_concurrency();
    for (int i = 0; i < threadpoolSize_; ++i) {
        subEventloops_.push_back(std::make_shared<event::Eventloop>());
    }
    for (int i = 0; i < threadpoolSize_; ++i) {
        auto subLoop = std::bind(&event::Eventloop::Loop, subEventloops_[i]);
        threadpool_->Add(subLoop);
    }
    acceptor_ = std::make_shared<net::TCPAcceptor>(eventloop_, ip, port);
}

} // namespace net