#include <iostream>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <memory>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iterator>

struct LocationData
{
    double lat;
    double lon;
    double alt;
    int64_t timestamp;
};

class CommandPrototypeFactory;
class GnssReceiver
{
public:
    GnssReceiver();
    ~GnssReceiver();
    void enableDebugMode();
    void disableDebugMode();
    bool getDebugMode();
    LocationData& getLocationData();
    void DEBUG();
    int processCommand(const std::string& command);

private:
    CommandPrototypeFactory* cmdFactory;
    bool m_debugMode;
    LocationData m_data;
};

class CommandPrototype
{
public:
    explicit CommandPrototype()
    {
    }
 
    virtual std::shared_ptr<CommandPrototype> clone() const = 0;
    virtual int execute(const std::vector<std::string>& args) = 0;
    virtual ~CommandPrototype() = default;
};
 
class EnableDebugModeCommand : public CommandPrototype
{
public:
    explicit EnableDebugModeCommand(GnssReceiver* receiver)
        : CommandPrototype()
    {
        pReceiver = receiver;
    }
 
    virtual std::shared_ptr<CommandPrototype> clone() const override
    {
        return std::make_shared<EnableDebugModeCommand>(*this);
    }

    virtual int execute(const std::vector<std::string>& args) override
    {
        if (pReceiver != nullptr)
        {
            pReceiver->enableDebugMode();
        }

        std::cout << "EnableDebugModeCommand executed" << std::endl;
        return 0;
    }
private:
    GnssReceiver* pReceiver;
};
 
class DisableDebugModeCommand : public CommandPrototype
{
public:
    explicit DisableDebugModeCommand(GnssReceiver* receiver)
        : CommandPrototype()
    {
        pReceiver = receiver;
    }
 
    virtual std::shared_ptr<CommandPrototype> clone() const override
    {
        return std::make_shared<DisableDebugModeCommand>(*this);
    }

    virtual int execute(const std::vector<std::string>& args) override
    {
        if (pReceiver != nullptr)
        {
            pReceiver->disableDebugMode();
        }

        std::cout << "DisableDebugModeCommand executed" << std::endl;
        return 0;
    }
private:
    GnssReceiver* pReceiver;
};
 
class InjectLatitudeCommand : public CommandPrototype
{
public:
    explicit InjectLatitudeCommand(GnssReceiver* receiver)
        : CommandPrototype()
    {
        pReceiver = receiver;
    }
 
    virtual std::shared_ptr<CommandPrototype> clone() const override
    {
        return std::make_shared<InjectLatitudeCommand>(*this);
    }

    virtual int execute(const std::vector<std::string>& args) override
    {
        if (pReceiver != nullptr && pReceiver->getDebugMode())
        {
            LocationData& data = pReceiver->getLocationData();
            data.lat = std::stoi(args[1]);
        }

        std::cout << "InjectLatitudeCommand executed" << std::endl;
        return 0;
    }
private:
    GnssReceiver* pReceiver;
};
 
class InjectLongitudeCommand : public CommandPrototype
{
public:
    explicit InjectLongitudeCommand(GnssReceiver* receiver)
        : CommandPrototype()
    {
        pReceiver = receiver;
    }
 
    virtual std::shared_ptr<CommandPrototype> clone() const override
    {
        return std::make_shared<InjectLongitudeCommand>(*this);
    }

    virtual int execute(const std::vector<std::string>& args) override
    {
        if (pReceiver != nullptr && pReceiver->getDebugMode())
        {
            LocationData& data = pReceiver->getLocationData();
            data.lon = std::stoi(args[1]);
        }
        std::cout << "InjectLongitudeCommand executed" << std::endl;
        return 0;
    }
private:
    GnssReceiver* pReceiver;
};

// Factory class
class CommandPrototypeFactory
{
public:
    explicit CommandPrototypeFactory(GnssReceiver* receiver)
    {
        command_list.insert(std::make_pair<std::string, std::shared_ptr<CommandPrototype>>("enableDebugMode", std::make_shared<EnableDebugModeCommand>(receiver)));
        command_list.insert(std::make_pair<std::string, std::shared_ptr<CommandPrototype>>("disableDebugMode", std::make_shared<DisableDebugModeCommand>(receiver)));
        command_list.insert(std::make_pair<std::string, std::shared_ptr<CommandPrototype>>("injectLat", std::make_shared<InjectLatitudeCommand>(receiver)));
        command_list.insert(std::make_pair<std::string, std::shared_ptr<CommandPrototype>>("injectLon", std::make_shared<InjectLongitudeCommand>(receiver)));
        // Add more commands here as needed
    }
 
    std::shared_ptr<CommandPrototype> createCommand(const std::string& command)
    {
        auto it = command_list.find(command);
        if (it != command_list.end() && it->second != nullptr)
        {
            return it->second->clone();
        }
        return nullptr;
    }
 
private:
    std::unordered_map<std::string, std::shared_ptr<CommandPrototype>> command_list;
};

// Implementation of GnssReceiver class
GnssReceiver::GnssReceiver()
{
    cmdFactory = new CommandPrototypeFactory(this);
    m_debugMode = false;
    m_data = {};
}

GnssReceiver::~GnssReceiver()
{
    
}

void GnssReceiver::enableDebugMode()
{
    m_debugMode = true;
}

void GnssReceiver::disableDebugMode()
{
    m_debugMode = false;
}

bool GnssReceiver::getDebugMode()
{
    return m_debugMode;
}

LocationData& GnssReceiver::getLocationData()
{
    return m_data;
}

void GnssReceiver::DEBUG()
{
    std::cout << m_data.timestamp << " " << m_data.lat << " " << m_data.lon << " " << m_data.alt << std::endl;
}

int GnssReceiver::processCommand(const std::string& command)
{
    // split string command to multiple tokens following the format:
    // <command> <value1> <value2> ... <valueN>
    std::istringstream iss(command);
    std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>());
    if (tokens.empty())
    {
        std::cout << "Can not handle an empty command";
        return -1;
    }

    std::shared_ptr<CommandPrototype> cmd = cmdFactory->createCommand(tokens[0]);
    if (cmd != nullptr)
    {
        return cmd->execute(tokens);
    }
    else
    {
        std::cout << "Command " << tokens[0] << " is not found in the factory" << std::endl;
    }

    return -1;
}

int main()
{
    GnssReceiver receiver;
    receiver.DEBUG();
    receiver.processCommand("enableDebugMode");
    receiver.processCommand("injectLat 18");
    receiver.processCommand("injectLon 106");
    receiver.processCommand("disableDebugMode");
    receiver.DEBUG();

    return 0;
}
