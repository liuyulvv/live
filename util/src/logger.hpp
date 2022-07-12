/**
 * @file logger.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-11
 */
#pragma once

#include <cassert>
#include <fstream>
#include <memory>
#include <mutex>
#include <string>

namespace util {

enum class LogLevel {
    DEBUG,
    INFO,
    ERROR 
};

class Logger final {
public:
    static Logger &GetLogger() {
        static Logger *logger_ = new Logger();
        return *logger_;
    }

public:
    void Init(Logger &logger, const std::string &filename, const LogLevel &level = LogLevel::DEBUG) {
        logger.Init(filename, level);
    }

    template <typename T, typename... args>
    Logger &operator()(const std::string &time, const LogLevel &level, const T &content, const args &...rest) {
        std::lock_guard<std::mutex> locker(mutex_);
        out_ << time;
        switch (level) {
        case LogLevel::DEBUG:
            out_ << " DEBUG ";
            break;
        case LogLevel::INFO:
            out_ << " INFO ";
            break;
        case LogLevel::ERROR:
            out_ << " ERROR ";
            break;
        default:
            out_ << " DEBUG ";
            break;
        }
        return this->operator()(content, rest...);
    }

private:
    Logger() = default;

    ~Logger() {
        out_.close();
    }

    void Init(const std::string &filename, const LogLevel &level = LogLevel::DEBUG) {
        level_ = level;
        out_ = std::ofstream(filename, std::ios::out);
        assert(out_.is_open());
    }

    template <typename T, typename... args>
    Logger &operator()(const T &content, const args &...rest) {
        out_ << content;
        return this->operator()(rest...);
    }

    template <typename T>
    Logger &operator()(const T &content) {
        out_ << content << std::endl;
        return *this;
    }

private:
    std::ofstream out_;
    LogLevel level_ = LogLevel::DEBUG;
    std::mutex mutex_;
};

}  // namespace util