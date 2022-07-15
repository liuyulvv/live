/**
 * @file buffer.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-11
 */

#pragma once

#include <queue>
#include <string>
#include <vector>

namespace util {
    
class Buffer final {
public:
    Buffer() = default;
    ~Buffer() = default;

public:
    char GetChar();
    std::vector<char> GetContent();
    std::vector<char> GetContent(int size);
    void Push(const std::string &content);
    void Push(const char* const content, int size);
    void Push(char content);
    void Push(const std::vector<char> &content);
    bool Empty() const;
    int Size() const;

private:
    std::queue<char> queue_;
};

} // namespace util