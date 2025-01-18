#include <iostream>
#include <vector>
#include <memory>

class i_command
{
public:
    i_command() = default;
    virtual ~i_command() = default;

    virtual void execute() = 0;
};

class i_device
{
public:
    i_device() = default;
    virtual ~i_device() = default;

    virtual void turn_on() = 0;
    virtual void turn_off() = 0;
    virtual void adjust_volume(int vol) = 0;
    virtual void switch_channel(int channel) = 0;
};

class turn_on_command : public i_command
{
public:
    turn_on_command(std::shared_ptr<i_device> p_device)
        : m_device(p_device)
    {
    }

    virtual void execute() override
    {
        m_device->turn_on();
    }

private:
    std::shared_ptr<i_device> m_device;
};

class turn_off_command : public i_command
{
public:
    turn_off_command(std::shared_ptr<i_device> p_device)
        : m_device(p_device)
    {
    }

    virtual void execute() override
    {
        m_device->turn_off();
    }

private:
    std::shared_ptr<i_device> m_device;
};

class adjust_volume_command : public i_command
{
public:
    adjust_volume_command(std::shared_ptr<i_device> p_device, int vol)
        : m_device(p_device)
        , m_volume(vol)
    {
    }

    virtual void execute() override
    {
        m_device->adjust_volume(m_volume);
    }

private:
    std::shared_ptr<i_device> m_device;
    int m_volume;
};

class switch_channel_command : public i_command
{
public:
    switch_channel_command(std::shared_ptr<i_device> p_device, int channel)
        : m_device(p_device)
        , m_channel(channel)
    {
    }

    virtual void execute() override
    {
        m_device->switch_channel(m_channel);
    }

private:
    std::shared_ptr<i_device> m_device;
    int m_channel;
};

class command_invoker
{
public:
    void add_command(std::shared_ptr<i_command> p_command)
    {
        m_commands.push_back(p_command);
    }

    void execute_commands()
    {
        for (auto& command : m_commands)
        {
            command->execute();
        }

        m_commands.clear();
    }

private:
    std::vector<std::shared_ptr<i_command>> m_commands;
};

class stupid_television : public i_device
{
public:
    virtual void turn_on() override
    {
        std::cout << "television is turned on" << std::endl;
    }

    virtual void turn_off() override
    {
        std::cout << "television is turned off" << std::endl;
    }

    virtual void adjust_volume(int vol) override
    {
        std::cout << "television volume = " << vol << std::endl;
    }

    virtual void switch_channel(int channel) override
    {
        std::cout << "television channel = " << channel << std::endl;
    }
};

class stupid_door : public i_device
{
public:
    virtual void turn_on() override
    {
        std::cout << "nah, turn on by yourself" << std::endl;
    }

    virtual void turn_off() override
    {
        std::cout << "this function is not supported, use your hand" << std::endl;
    }

    virtual void adjust_volume(int vol) override
    {
        std::cout << "this feature is not supported" << std::endl;
    }

    virtual void switch_channel(int channel) override
    {
        std::cout << "this feature is not supported" << std::endl;
    }
};

int main()
{
    command_invoker invoker;

    std::shared_ptr<stupid_door> p_door = std::make_shared<stupid_door>();
    std::shared_ptr<stupid_television> p_tel = std::make_shared<stupid_television>();

    invoker.add_command(std::make_shared<turn_on_command>(p_door));
    invoker.add_command(std::make_shared<turn_on_command>(p_tel));
    invoker.add_command(std::make_shared<adjust_volume_command>(p_door, 10));
    invoker.add_command(std::make_shared<adjust_volume_command>(p_tel, 10));
    invoker.add_command(std::make_shared<switch_channel_command>(p_tel, 5));
    invoker.add_command(std::make_shared<turn_off_command>(p_door));
    invoker.add_command(std::make_shared<turn_off_command>(p_tel));

    invoker.execute_commands();

    return 0;
}