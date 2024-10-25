#ifndef THREAD_SAFE_QUEUE_HPP_INCLUDED
#define THREAD_SAFE_QUEUE_HPP_INCLUDED

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

template<typename T>
class ThreadsafeQueue
{
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T> > data_queue;
    std::condition_variable data_cond;
public:
    ThreadsafeQueue() = default;

    void wait_and_pop(T &value);

    bool try_pop(T &value);

    std::shared_ptr<T> wait_and_pop();

    std::shared_ptr<T> try_pop();

    bool empty() const;

    void push(T new_value);
    
};

#include "threadsafeQueue-private.hpp"

#endif
