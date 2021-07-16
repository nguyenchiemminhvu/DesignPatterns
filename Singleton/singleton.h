#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <pthread.h>

template <class T>
class Singleton
{
public:
    static T * GetInstance();

private:
    static pthread_mutex_t s_locker;
    static T * s_instance;
};

template <class T>
T * Singleton<T>::s_instance = nullptr;

template <class T>
pthread_mutex_t Singleton<T>::s_locker;

template <class T>
T * Singleton<T>::GetInstance()
{
    if (s_instance == nullptr)
    {
        pthread_mutex_lock(&s_locker);
        if (s_instance == nullptr)
        {
            s_instance = new T();
        }
        pthread_mutex_unlock(&s_locker);
    }

    return s_instance;
}

#endif // __SINGLETON_H__