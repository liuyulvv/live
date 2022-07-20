/**
 * @file threadpool.hpp
 * @author liuyulvv (liuyulvv@outlook.com)
 * @version 0.1
 * @date 2022-07-11
 */

#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace util {

class ThreadPool final {
    public:
        explicit ThreadPool(int size = std::thread::hardware_concurrency()) {
            for (int i = 0; i < size; ++i) {
                threads_.emplace_back(std::thread([this]() {
                    std::unique_lock<std::mutex> locker(mtx_);
                    while (true) {
                        if (!tasks_.empty()) {
                            auto task = std::move(tasks_.front());
                            tasks_.pop();
                            locker.unlock();
                            task();
                            locker.lock();
                        } else {
                            cv_.wait(locker);
                        }
                    }
                }));
            }
        }

        ~ThreadPool() {
            {
                std::unique_lock<std::mutex> locker(mtx_);
            }
            cv_.notify_all();
        }

        template <typename F>
        void Add(F&& f) {
            {
                std::unique_lock<std::mutex> locker(mtx_);
                tasks_.emplace(std::forward<F>(f));
            }
            cv_.notify_one();
        }

    private:
        std::vector<std::thread> threads_;
        std::queue<std::function<void()>> tasks_;
        std::mutex mtx_;
        std::condition_variable cv_;
};

}  // namespace util