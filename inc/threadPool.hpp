
#ifndef THREAD_POOL_HPP_INCLUDED
#define THREAD_POOL_HPP_INCLUDED

#include "threadsafeQueue.hpp"
#include "joinThreads.hpp"

#include <thread>
#include <vector>
#include <functional>
#include <type_traits>
#include <iostream>
#include <future>
#include <atomic>
#include "FunctionWrapper.hpp"

// Custom Threadpool for Serialism Generation
class ThreadPool
{
    
    std::atomic_bool done_;
    ThreadsafeQueue<FunctionWrapper> work_queue_;
    std::vector<std::thread> threads_;
    JoinThreads joiner_;
    unsigned int numThreads_;

    void worker_thread();

    unsigned int calcNumThreads(unsigned int numThreads = UINT_MAX);

public:
    ThreadPool(unsigned int numThreads = UINT_MAX);

    ~ThreadPool();

    bool isDone();

    template <typename FunctionType>
    std::future<typename std::invoke_result_t<FunctionType>> submit(FunctionType f);
};

template<typename FunctionType>
std::future<typename std::invoke_result_t<FunctionType>> ThreadPool::submit(FunctionType f)
{
    typedef typename std::invoke_result_t<FunctionType> result_type;
    
    std::packaged_task<result_type()> task(std::move(f));
    std::future<result_type> res(task.get_future());
    work_queue_.push(std::move(task));
    return res;
}

#endif //THREAD_POOL_HPP_INCLUDED
