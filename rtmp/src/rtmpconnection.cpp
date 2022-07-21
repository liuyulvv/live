/**
 * @file rtmpconnection.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#include "rtmpconnection.hpp"
#include "util.hpp"

namespace rtmp {

namespace {
const int BASIC_HEADER_SIZE = 1;
const int TYPE_0_SIZE = 11;
}  // namespace

RTMPConnection::RTMPConnection(const SEventloop& eventloop, int fd, bool et) : TCPConnection(eventloop, fd, et) {
}

RTMPStatus RTMPConnection::GetStatus() const {
    return status_;
}

void RTMPConnection::SetStatus(const RTMPStatus& status) {
    status_ = status;
}

void RTMPConnection::OnStreamData() {
    auto header = Recv(BASIC_HEADER_SIZE);
    auto fmt = header[0] >> 6;
    auto id = header[0] << 2 >> 2;
    switch (fmt) {
        case 0: {
            break;
        }
    }
}

}  // namespace rtmp