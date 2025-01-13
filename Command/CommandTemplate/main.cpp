#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <functional>
#include <tuple>
#include <memory>

class Receiver
{
public:
};

class ICommand
{
public:
    ICommand() = default;
    virtual void execute() = 0;
};

template <class Receiver, typename... Args>
class TemplateCommand : public ICommand
{
public:
    using Action = void (Receiver::*)(Args...);

    TemplateCommand(std::shared_ptr<Receiver> p_recv, Action act, Args... args)
        : m_receiver(p_recv), m_action(act), m_args(std::make_tuple<Args...>(args...))
    {

    }

    virtual void execute()
    {
        this->invoke(std::make_index_sequence<sizeof...(Args)>());
    }

private:
    template <std::size_t... Indices>
    void invoke(std::index_sequence<Indices...>)
    {
        if (m_receiver != nullptr)
        {
            m_receiver->*m_action(std::get<Indices>(m_args)...);
        }
    }

private:
    std::shared_ptr<Receiver> m_receiver;
    Action m_action;
    std::tuple<Args...> m_args;
};

int main()
{
    return 0;
}