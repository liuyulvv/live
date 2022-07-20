/**
 * @file util.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-11
 */
#pragma once

#include "alias.hpp"
#include "logger.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace util {

static std::string NowString(const std::string& format = "%Y-%m-%d %H:%M:%S.", bool with_ms = true, bool utc8 = true) {
    auto tp = std::chrono::system_clock::now();
    auto tt = tp.time_since_epoch();
    time_t durS = std::chrono::duration_cast<std::chrono::seconds>(tt).count();
    std::ostringstream ss;
    if (std::tm* tm = (utc8 ? std::gmtime(&durS) : std::localtime(&durS))) {
        tm->tm_hour += 8;
        if (tm->tm_hour >= 24) {
            tm->tm_hour -= 24;
        }
        ss << std::put_time(tm, format.c_str());
        if (with_ms) {
            Int64 durMs = std::chrono::duration_cast<std::chrono::milliseconds>(tt).count();
            ss << std::setw(3) << std::setfill('0') << static_cast<UInt16>(durMs - durS * 1000);
        }
    }
    return ss.str();
}

static Int64 Now() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

static util::Logger& GetLogger(const std::string& pathname) {
    auto& logger = Logger::GetLogger();
    Logger::Init(logger, pathname + ".log");
    return logger;
}

template <typename T, typename... Args>
void Debug(const T& content, const Args&... rest) {
    auto& out = util::Logger::GetLogger();
    out(util::NowString(), util::LogLevel::DEBUG, content, rest...);
}

template <typename T, typename... Args>
void Info(const T& content, const Args&... rest) {
    auto& out = util::Logger::GetLogger();
    out(util::NowString(), util::LogLevel::INFO, content, rest...);
}

template <typename T, typename... Args>
void Error(const T& content, const Args&... rest) {
    auto& out = util::Logger::GetLogger();
    out(util::NowString(), util::LogLevel::ERROR, content, rest...);
}

static Int32 CharsToInt(const std::vector<char>& chars) {
    auto size = chars.size();
    Int32 ret = 0;
    for (const auto c : chars) {
    }
    return ret;
}

}  // namespace util