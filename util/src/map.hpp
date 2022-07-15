/**
 * @file map.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-11
 */

#pragma once

#include <map>
#include <mutex>

namespace util {

template <typename T1, typename T2>
class Map final {
public:
    Map() = default;
    ~Map() = default;

public:
    void Insert(const T1 &key, const T2 &value) {
        std::lock_guard<std::mutex> locker(mutex_);
        map_[key] = value;
    }

    void Erase(const T1 &key) {
        std::lock_guard<std::mutex> locker(mutex_);
        map_.erase(key);
    }

    T2& Get(const T1 &key) {
        std::lock_guard<std::mutex> locker(mutex_);
        return map_[key];
    }

private:
    std::map<T1, T2> map_;
    std::mutex mutex_;
};

} // namespace util