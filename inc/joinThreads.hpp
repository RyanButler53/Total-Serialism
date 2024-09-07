#ifndef JOIN_THREADS_HPP_INCLUDED
#define JOIN_THREADS_HPP_INCLUDED

#include <vector>
#include <thread>
class JoinThreads
{
private:
    std::vector<std::thread>& threads_;
public:
    explicit JoinThreads(std::vector<std::thread>& threads);
    ~JoinThreads();
};

#endif //JOIN_THREADS_HPP_INCLUDED