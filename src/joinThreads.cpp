#include "joinThreads.hpp"

JoinThreads::JoinThreads(std::vector<std::thread>& threads):threads_{threads}
{}

// Thread Joining is handled in the destructor so all threads are cleared up.
JoinThreads::~JoinThreads()
{
    for (size_t i = 0; i < threads_.size(); ++i)
    {
        if(threads_[i].joinable()){
            threads_[i].join();
        }
        // Not Joinable case: Means an exception is thrown
    }
}
