/**
 * @file rtmpserver.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#include "rtmpserver.hpp"
#include "rtmpconnection.hpp"
#include "util.hpp"
#include <random>

namespace rtmp {

namespace {
const int RTMP_VERSION_SIZE = 1;
const int RTMP_ZERO_SIZE = 4;
const int RTMP_TIMESTAMP_SIZE = 4;
const int C0_SIZE = 1;
const int C1_SIZE = 1536;
const int C2_SIZE = 1536;
const int RANDOM_DATA_SIZE = C1_SIZE - RTMP_TIMESTAMP_SIZE - RTMP_ZERO_SIZE;
}  // namespace

RTMPServer::RTMPServer(const SEventloop& eventloop, const std::string& ip, unsigned port) : TCPServer(eventloop, ip, port) {
    GenerateRandomData(serverTimestamp_, RTMP_TIMESTAMP_SIZE);
    GenerateRandomData(serverRandomData_, C1_SIZE - RTMP_TIMESTAMP_SIZE - RTMP_ZERO_SIZE);
    acceptor_->SetNewConnectionCallback([&](int sockfd, const net::Address& address) {
        auto connection = std::make_shared<RTMPConnection>(subEventloops_[sockfd % threadpoolSize_], sockfd);
        connection->SetReadCallback([&](const STCPConnection& connection) {
            auto conn = connection_.Get(connection->GetFd());
            switch (conn->GetStatus()) {
                case RTMPStatus::UNINITIALIZED: {
                    OnProcessC0AndC1(conn);
                    break;
                }
                case RTMPStatus::ACK_SEND: {
                    OnProcessC2(conn);
                    if (!conn->HasContent()) {
                        break;
                    }
                }
                case RTMPStatus::HANDSHAKE_DOWN: {
                    conn->OnStreamData();
                    break;
                }
            }
        });
        connection->SetCloseCallback([&](const STCPConnection& connection) {
            connection_.Erase(connection->GetFd());
        });
        connection->SetAddress(address);
        connection->EnableRead();
        connection_.Insert(sockfd, connection);
    });
}

void RTMPServer::GenerateRandomData(std::vector<char>& object, int size) {
    std::random_device rd;
    std::mt19937 seed(rd());
    std::uniform_int_distribution<> gen(0, 255);
    object.clear();
    for (int i = 0; i < size; ++i) {
        object.push_back(gen(seed));
    }
}

void RTMPServer::OnProcessC0AndC1(SRTMPConnection& conn) {
    auto c0Request = conn->Recv(C0_SIZE);
    assert(c0Request.size() == C0_SIZE);
    if (c0Request[0] != serverRTMPVersion_) {
        conn->HandleClose(conn);
        return;
    }
    auto c1Request = conn->Recv(C1_SIZE);
    clientTimestamp_ = std::vector<char>(c1Request.begin(), c1Request.begin() + RTMP_TIMESTAMP_SIZE);
    clientRamdomData_ = std::vector<char>(c1Request.begin() + RTMP_TIMESTAMP_SIZE + RTMP_ZERO_SIZE, c1Request.end());
    GenerateRandomData(serverTimestamp_, RTMP_TIMESTAMP_SIZE);
    conn->Write(serverRTMPVersion_);
    conn->Write(serverTimestamp_);
    conn->Write(RTMP_ZERO_SIZE, 0);
    conn->Write(serverRandomData_);
    conn->Write(serverTimestamp_);
    conn->Write(RTMP_ZERO_SIZE, 0);
    conn->Write(clientRamdomData_);
    conn->Send();
    conn->SetStatus(RTMPStatus::ACK_SEND);
}

void RTMPServer::OnProcessC2(SRTMPConnection& conn) {
    auto request = conn->Recv(C2_SIZE);
    auto serverRandomData = std::vector<char>(request.begin() + 2 * RTMP_TIMESTAMP_SIZE, request.end());
    if (serverRandomData == serverRandomData_) {
        conn->SetStatus(RTMPStatus::HANDSHAKE_DOWN);
    } else {
        conn->HandleClose(conn);
    }
}

}  // namespace rtmp