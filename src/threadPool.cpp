#include "threadPool.hpp"

ThreadPool::ThreadPool(unsigned int numThreads): 
done_(false), 
joiner_{threads_}, 
numThreads_{calcNumThreads(numThreads)}{
    try
    {
        for(unsigned i=0;i<numThreads_;++i) {
            threads_.push_back(
                std::thread(&ThreadPool::worker_thread,this));
        }
    } catch (std::exception &e) {
        done_ = true;
        throw;
    }
}


unsigned int ThreadPool::calcNumThreads(unsigned int numThreads){
    unsigned int hardwareMax = std::thread::hardware_concurrency();
    if (hardwareMax == 0){ // if less than 2 or error
        return 2;
    } else {
        return std::min(numThreads, hardwareMax);
    }
}
ThreadPool::~ThreadPool()
{
    done_ = true;
}

void ThreadPool::worker_thread(){
    while(!done_) {
        FunctionWrapper task;
        if(work_queue_.try_pop(task)) {
            task();
        } else {
            std::this_thread::yield();
        }
    }
}

bool ThreadPool::isDone(){
    return done_;
}