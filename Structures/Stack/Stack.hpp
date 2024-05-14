#ifndef STRUCTURES_STACK_STACK_HPP
#define STRUCTURES_STACK_STACK_HPP

#include "../Common/Node/SingleNode.hpp"

template <typename T>
class Stack
{
private:
    SingleNode<T>* head_;
    size_t size_;
    bool isEmpty_;
public:
    Stack() : head_(nullptr), size_(0), isEmpty_(true) { std::cout << "Created empty Stack at " << this << std::endl; }
    Stack(SingleNode<T>* initHead);
    ~Stack();

    // Methods
    void parse() const;
    void insert(const T& newData);
    void insert(SingleNode<T>* newNode);
    void pop();
    SingleNode<T>* peek() const { return this->head_; }

    // Getters
    size_t getSize() const { return this->size_; }
    bool isEmpty() const { return this->isEmpty_; }
};

#endif