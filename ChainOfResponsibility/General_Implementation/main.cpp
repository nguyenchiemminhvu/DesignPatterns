#include <iostream>
#include <memory>
#include <string>

// Abstract Handler
class Handler
{
protected:
    std::shared_ptr<Handler> next;

public:
    virtual ~Handler() = default;

    void setNext(std::shared_ptr<Handler> nextHandler)
    {
        next = nextHandler;
    }

    virtual void handle(const std::string &request)
    {
        if (next)
        {
            next->handle(request);
        }
        else
        {
            std::cout << "Request not handled.\n";
        }
    }
};

class ConcreteHandler1 : public Handler
{
public:
    void handle(const std::string &request) override
    {
        if (request == "Request1")
        {
            std::cout << "ConcreteHandler1 handled the request.\n";
        }
        else
        {
            Handler::handle(request);
        }
    }
};

class ConcreteHandler2 : public Handler
{
public:
    void handle(const std::string &request) override
    {
        if (request == "Request2")
        {
            std::cout << "ConcreteHandler2 handled the request.\n";
        }
        else
        {
            Handler::handle(request);
        }
    }
};

int main()
{
    // Create handlers
    auto handler1 = std::make_shared<ConcreteHandler1>();
    auto handler2 = std::make_shared<ConcreteHandler2>();

    // Build the chain
    handler1->setNext(handler2);

    // Client sends requests to the chain
    handler1->handle("Request1"); // Output: ConcreteHandler1 handled the request.
    handler1->handle("Request2"); // Output: ConcreteHandler2 handled the request.
    handler1->handle("UnknownRequest"); // Output: Request not handled.

    return 0;
}