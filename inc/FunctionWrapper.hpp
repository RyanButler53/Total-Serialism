#include <memory>

#ifndef FUNCTION_WRAPPER_HPP_INCLUDED
#define FUNCTION_WRAPPER_HPP_INCLUDED


class FunctionWrapper
{
    struct impl_base { // Type Erasure Idiom
        virtual void call()=0;
        virtual ~impl_base() {}
    };
    std::unique_ptr<impl_base> impl;
    template<typename F>
    struct impl_type: impl_base
    {
        F f;
        impl_type(F&& f_): f(std::move(f_)) {}
        void call() { f(); }
    };
public:
    template<typename F>
    FunctionWrapper(F&& f):
        impl(new impl_type<F>(std::move(f)))
    {}

    FunctionWrapper() = default;

    void operator()() { impl->call(); };

    FunctionWrapper(FunctionWrapper&& other):
        impl(std::move(other.impl))
    {}

    FunctionWrapper& operator=(FunctionWrapper&& other)
    {
        impl=std::move(other.impl);
        return *this;
    }

    FunctionWrapper(const FunctionWrapper&)=delete;
    FunctionWrapper(FunctionWrapper&)=delete;
    FunctionWrapper& operator=(const FunctionWrapper&)=delete;
};

#endif // FUNCTION_WRAPPER_HPP_INCLUDED