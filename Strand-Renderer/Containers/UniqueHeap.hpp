#pragma once

typedef decltype(__nullptr) NullPtrType;

template<typename T, typename...Args>
class UniqueHeap
{
public:
    UniqueHeap() : DataPtr_(nullptr)
    {}

    UniqueHeap(T* ptr) : DataPtr_(ptr)
    {}

    UniqueHeap(UniqueHeap<T>&& other)
    {
        DataPtr_ = other.DataPtr_;
        other.DataPtr_ = nullptr;
    }

    UniqueHeap<T>& operator=(UniqueHeap<T>&& other)
    {
        if(this != &other) {
            delete DataPtr_;
            DataPtr_ = other.DataPtr_;
            other.DataPtr_ = nullptr;
        }
        return *this;
    }

    ~UniqueHeap()
    {
        delete DataPtr_;
    }

    T& operator*()
    {
        return *DataPtr_;
    }

    T* operator->()
    {
        return DataPtr_;
    }

    T* GetData()
    {
        return DataPtr_;
    }

    void Reset()
    {
        delete DataPtr_;
    }

    void Replace(T* ptr)
    {
        delete DataPtr_;
        DataPtr_ = ptr;
    }

    bool operator==(NullPtrType) const
    {
        return DataPtr_ == nullptr;
    }

    bool operator!=(NullPtrType) const
    {
        return DataPtr_ != nullptr;
    }

    bool operator==(const UniqueHeap<T>& other) const
    {
        return DataPtr_ == other;
    }

    bool operator!=(const UniqueHeap<T>& other) const
    {
        return DataPtr_ != other;
    }

private:
    T* DataPtr_;
};

template<typename T, typename...Args>
UniqueHeap<T> MakeUniqueHeap(Args&& ...args)
{
    return UniqueHeap<T>(new T(args...));
}