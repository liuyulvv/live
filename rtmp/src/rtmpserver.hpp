/**
 * @file rtmpserver.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#pragma once

#include "address.hpp"
#include "eventloop.hpp"
#include "map.hpp"
#include "rtmpconnection.hpp"
#include "tcpacceptor.hpp"
#include "tcpserver.hpp"
#include "threadpool.hpp"
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace rtmp {

class RTMPServer final : public net::TCPServer {
    public:
        using SEventloop = std::shared_ptr<event::Eventloop>;
        using STCPConnection = std::shared_ptr<net::TCPConnection>;
        using SRTMPConnection = std::shared_ptr<RTMPConnection>;

        RTMPServer(const SEventloop& eventloop, const std::string& ip, unsigned port);
        ~RTMPServer() override = default;

    private:
        static void GenerateRandomData(std::vector<char>& object, int size);
        void OnProcessC0AndC1(SRTMPConnection& conn);
        void OnProcessC2(SRTMPConnection& conn);

        const char serverRTMPVersion_ = 3;
        std::vector<char> serverTimestamp_;
        std::vector<char> serverRandomData_;
        std::vector<char> clientTimestamp_;
        std::vector<char> clientRamdomData_;

        int chunkSize_ = 0;

        util::Map<int, SRTMPConnection> connection_;
};

}  // namespace rtmp