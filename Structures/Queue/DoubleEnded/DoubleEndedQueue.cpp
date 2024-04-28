#include <iostream>
#include <sstream>

#include "./DoubleEndedQueue.hpp"

Deque::Deque(size_t capacity) : data_{0}, front_(-1), rear_(-1), capacity_(capacity), size_(0), isEmpty_(true)
{
    std::cout << "Created a Double Ended Queue" << std::endl; 
    std::cout << "DBG: front=" << front_ << " rear=" << rear_ << " size=" << size_ << " isEmpty=" << std::boolalpha << isEmpty_ << std::endl;
}


void Deque::insertFront(int value)
{
    if(size_ == capacity_)
    {
        std::cout << "Could not add new value - deque is full!" << std::endl;
        return;
    }

    std::cout << "Enqueing " << value << " in front of the Deque\n";
    
    // Given deque is empty
    if(isEmpty_)
    {
        front_ = 0;
        rear_  = 0;
        data_[front_] = value;
        isEmpty_ = false;
    }
    else
    {
        front_ == 0 ? front_ = capacity_ - 1 : --front_;
        // Check if front == back
        if(front_ == rear_)
        {
            std::stringstream errMsg("");
            errMsg << "Impossible Error " << front_ << " = " << rear_ << std::endl;
            throw errMsg.str();
        }
        data_[front_] = value;
    }

    ++size_;
    std::cout << "Successfully enqued new value " << value << " at pos " << front_ << " (front)" << "\n";
    std::cout << "DBG: front=" << front_ << " rear=" << rear_ << " size=" << size_ << " isEmpty=" << std::boolalpha << isEmpty_ << std::endl;

}

void Deque::removeFront()
{
    if(isEmpty_)
    {
        std::cout << "Cannot remove front - deque is empty" << std::endl;
        return;
    }

    int deletedValue = data_[front_];
    data_[front_] = 0;
    std::cout << "Deleting front (value " << deletedValue << ")\n"; 
    if(front_ == rear_) // This scenario occurs only when 1 value is left
    {
        front_ = -1;
        rear_  = -1;
        isEmpty_ = true;
    }
    else
    {
        front_ == static_cast<long>(capacity_ - 1) ? front_ = 0 : ++front_;
    }
    --size_;
    std::cout << "Successfully dequed new value " << deletedValue << " from deque\n";
    std::cout << "DBG: front=" << front_ << " rear=" << rear_ << " size=" << size_ << " isEmpty=" << std::boolalpha << isEmpty_ << std::endl;
}

void Deque::insertRear(int value)
{
    std::cout << "DBG: size=" << size_ << " capacity_=" << capacity_ << "\n";
    if(size_ == capacity_)
    {
        std::cout << "Could not add new value - deque is full!" << std::endl;
        return;
    }

    std::cout << "Enqueing " << value << " at the rear of the Deque\n";

    if(isEmpty_)
    {
        front_ = 0;
        rear_  = 0;
        data_[rear_] = value;
        isEmpty_ = false;
    }
    else
    {
        rear_ == static_cast<long>(capacity_ - 1) ? rear_ = 0 : ++rear_;
        if(front_ == rear_)
        {
            std::stringstream errMsg("");
            errMsg << "Impossible Error " << front_ << " = " << rear_ << std::endl;
            throw errMsg.str();
        }
        data_[rear_] = value;
    }

    ++size_;
    std::cout << "Successfully enqued new value " << value << " at pos " << rear_ << " (rear)"<< "\n";
    std::cout << "DBG: front=" << front_ << " rear=" << rear_ << " size=" << size_ << " isEmpty=" << std::boolalpha << isEmpty_ << std::endl;
}
void Deque::removeRear()
{
    if(isEmpty_)
    {
        std::cout << "Cannot remove rear - deque is empty" << std::endl;
        return;
    }

    int deletedValue = data_[rear_];
    std::cout << "Deleting rear (value " << deletedValue << ")\n";
    if(front_ == rear_)
    {
        front_   = -1;
        rear_    = -1;
        isEmpty_ = true;
    }
    else
    {
        rear_ == static_cast<long>(capacity_ - 1) ? rear_ = 0 : --rear_;
    }
    --size_;
    std::cout << "Successfully dequed new value " << deletedValue << " from deque\n";
    std::cout << "DBG: front=" << front_ << " rear=" << rear_ << " size=" << size_ << " isEmpty=" << std::boolalpha << isEmpty_ << std::endl;
}

/// @brief Return N-th value the deque
/// @param pos N-th position
/// @warning Can get out of bounds resulting in sigkill
/// @return Value of N-th position
int& Deque::operator[](size_t pos)
{
    size_t index = front_ + pos;
    if(index >= capacity_) index = index % capacity_;
    return data_[index];
}