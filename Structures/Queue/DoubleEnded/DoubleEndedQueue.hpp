#ifndef STRUCTURES_QUEUE_DOUBLEENDED_DOUBLEENDEDQUEUE_HPP
#define STRUCTURES_QUEUE_DOUBLEENDED_DOUBLEENDEDQUEUE_HPP


#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned long size_t;
#endif

#define MAX_QUEUE_SIZE 160

class Deque
{
private:
    int data_[MAX_QUEUE_SIZE];
    long front_;
    long rear_;
    size_t capacity_;
    size_t size_;
    bool isEmpty_;
public:

    Deque(size_t capacity = MAX_QUEUE_SIZE);
    ~Deque() = default;

    void insertFront(int value);
    void removeFront();
    void insertRear(int value);
    void removeRear();

    int peekFront() const { return data_[front_]; } 
    int peekRear()  const { return data_[rear_];  }

    bool isEmpty() const { return isEmpty_; }
    size_t getSize() const { return size_; }

    int& operator[](size_t pos);

};

#endif