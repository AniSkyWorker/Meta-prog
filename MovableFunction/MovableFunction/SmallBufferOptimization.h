#pragma once
#include <memory>
#include <utility>

namespace movable_function::optimization
{
template<typename ReturnType, typename ...Args>
class FunctionInterface
{
public:
    virtual ~FunctionInterface() = default;

    virtual ReturnType operator()(Args&&...) const = 0;
};

template<typename Func, typename ReturnType, typename ...Args>
class FunctionImpl final : public FunctionInterface<ReturnType, Args...>
{
public:
    FunctionImpl(Func&& func)
        : m_fn(std::move(func))
    {
    }

    ReturnType operator()(Args&& ...args) const override
    {
        return std::invoke(m_fn, std::forward<Args>(args)...);
    }

private:
    Func m_fn;
};

template<typename FuncDeclaration>
class MovableFunction;

template<typename ReturnType, typename ...Args>
class MovableFunction <ReturnType(Args...)>
{
public:
    MovableFunction() {}

    template<class Func>
    MovableFunction(Func&& fn)
    {
        if constexpr(sizeof(FunctionImpl<Func, ReturnType, Args...>) > BUFFER_SIZE)
        {
            m_pImplUnique = std::unique_ptr(std::forward<Func>(fn));
            m_pImpl = m_pImplUnique.get();
        }
        else
        {
            m_pImpl = new (&m_buffer) FunctionImpl<Func, ReturnType, Args...>{ std::forward<FunctionImpl<Func, ReturnType, Args...>>(fn) };
        }
    }

    ReturnType operator()(Args&&...args) const
    {
        if (m_pImpl)
        {
            return std::invoke(*m_pImpl, std::forward<Args>(args)...);
        }

        throw std::bad_function_call();

    }

private:
    std::unique_ptr<FunctionInterface<ReturnType, Args...>> m_pImplUnique;
    constexpr int BUFFER_SIZE = 128;
    char m_buffer[BUFFER_SIZE];
    FunctionInterface<ReturnType, Args...> * m_pImpl;
};
}