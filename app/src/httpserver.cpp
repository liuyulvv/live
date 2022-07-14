/**
 * @file httpserver.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-14
 */

#include "httpserver.hpp"
#include "util.hpp"

namespace app {

HTTPServer::HTTPServer(const SEventloop &eventloop, const std::string &ip, const unsigned &port) : TCPServer(eventloop, ip, port) {
    SetReadCallback(std::bind(&HTTPServer::HandleRead, this, std::placeholders::_1));
}

void HTTPServer::HandleRead(const STCPConnection &connection) {
    util::Info("read message.");
    std::vector<std::string> header(3, "");
    auto request = connection->Recv();
    int index = 0;
    for (int i = 0; i < request.size(); ++i) {
        if (request[i] == '\r' && i + 1 < request.size() && request[i + 1] == '\n') {
            break;
        }
        if (request[i] != ' ') {
            header[index] += request[i];
        }
        else {
            ++index;
        }
    }
    header[1].erase(header[1].begin());
    std::string body;
    body += "<html><title>" + header[0] + "</title>";
    body += "<body>" + header[1] + "<body/></html>";
    std::string status("HTTP/1.1 200 OK\r\n");
    std::string serverInfo("Server:TestHTTP server\r\n");
    std::string contentLength("Content-length:" + std::to_string(body.size()) + "\r\n");
    std::string contentType("Content-type:text/html\r\n\r\n");
    std::string response = status + serverInfo + contentLength + contentType + body;
    connection->Write(response);
    connection->Send();
    util::Info("send message.");
    HandleClose(connection);
}

} // namespace app