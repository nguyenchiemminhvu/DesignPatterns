#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <memory>
#include <queue>

template <typename T>
class Singleton {
public:
    static T& getInstance() {
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
    ~Singleton() = default;
};
 
class MySingleton : public Singleton<MySingleton> {
public:
    void doSomething() {
        // Implement your singleton logic here
    }

    // Add any other member functions or variables as needed
};

int main()
{
    MySingleton& instance = MySingleton::getInstance();
    instance.doSomething();

    return 0;
}
