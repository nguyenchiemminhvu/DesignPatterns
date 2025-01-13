#include <unistd.h>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <functional>
#include <tuple>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

class Receiver
{
public:
    void handle_string(std::string s)
    {
        std::cout << __func__ << "(" << s << ")" << std::endl;
    }

    void handle_int_int(int a, int b)
    {
        std::cout << __func__ << "(" << a << ", " << b << ")" << std::endl;
    }
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
        : m_receiver(p_recv), m_action(act), m_args(std::make_tuple(args...))
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
            (m_receiver.get()->*m_action)(std::get<Indices>(m_args)...);
        }
    }

private:
    std::shared_ptr<Receiver> m_receiver;
    Action m_action;
    std::tuple<Args...> m_args;
};

class EventQueue
{
public:
    EventQueue()
    {
        m_runner = std::thread(&EventQueue::run, this);
        m_runner.detach();
    }

    void add_command(std::shared_ptr<ICommand> p_command)
    {
        std::unique_lock<std::mutex> lock(m_mut);
        m_queue.push(std::move(p_command));
        lock.unlock();
        m_cond.notify_one();
    }

private:
    void run()
    {
        while (true)
        {
            std::shared_ptr<ICommand> cur_command;

            std::unique_lock<std::mutex> lock(m_mut);
            m_cond.wait(lock, [&]() {
                return !m_queue.empty();
            });

            cur_command = std::move(m_queue.front());
            m_queue.pop();
            lock.unlock();

            cur_command->execute();
        }
    }

private:
    std::queue<std::shared_ptr<ICommand>> m_queue;
    std::thread m_runner;
    std::mutex m_mut;
    std::condition_variable m_cond;
};

int main()
{
    Receiver event_handler;

    EventQueue event_queue;
    event_queue.add_command(std::make_shared<TemplateCommand<Receiver, std::string>>(std::make_shared<Receiver>(event_handler), &Receiver::handle_string, "test"));
    usleep(1000000);
    event_queue.add_command(std::make_shared<TemplateCommand<Receiver, int, int>>(std::make_shared<Receiver>(event_handler), &Receiver::handle_int_int, 1, 2));
    
    while (true)
    {
        pause();
    }

    return 0;
}