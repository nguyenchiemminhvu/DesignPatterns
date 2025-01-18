#include <iostream>
#include <vector>

class i_command
{
public:
    virtual void execute() = 0;
};

class i_device
{
public:
    virtual void turn_on() = 0;
    virtual void turn_off() = 0;
    virtual void adjust_volume(int vol) = 0;
    virtual void switch_channel(int channel) = 0;
};

class turn_on_command : public i_command
{
public:

};

class turn_off_command : public i_command
{
public:

};

class adjust_volume_command : public i_command
{
public:

};

class switch_channel_command : public i_command
{
public:

};

class command_invoker
{
public:

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
    return 0;
}