/**
 * @file buffer.cpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-11
 */

#include "buffer.hpp"

namespace util {

char Buffer::GetChar() {
    char c = queue_.front();
    queue_.pop();
    return c;
}

std::vector<char> Buffer::GetContent() {
    std::vector<char> content;
    while (!queue_.empty()) {
        content.push_back(queue_.front());
        queue_.pop();
    }
    return content;
}

std::vector<char> Buffer::GetContent(int size) {
    std::vector<char> content;
    int index = 0;
    while (!queue_.empty() && index < size) {
        content.push_back(queue_.front());
        queue_.pop();
        ++index;
    }
    return content;
}

void Buffer::Push(const std::string &content) {
    for (const auto &c : content) {
        queue_.push(c);
    }
}

void Buffer::Push(const char *content, int size) {
    for (int i = 0; i < size; ++i) {
        queue_.push(content[i]);
    }
}

void Buffer::Push(const char &content) {
    queue_.push(content);
}

void Buffer::Push(const std::vector<char> &content) {
    for (const auto &c : content) {
        queue_.push(c);
    }
}

bool Buffer::Empty() const {
    return queue_.empty();
}

} // namespace util