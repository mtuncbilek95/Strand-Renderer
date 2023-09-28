#pragma once

template<typename T>
class Singleton
{
public:
    Singleton(const Singleton& instance) = delete;
    Singleton& operator=(const Singleton& instance) = delete;

    static T& GetInstance()
    {
        static T instance;
        return instance;
    }

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};
