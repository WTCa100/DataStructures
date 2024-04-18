#ifndef STRUCTURES_STACK_STACK_HPP
#define STRUCTURES_STACK_STACK_HPP

#include "../Common/Node/SingleNode.hpp"

class Stack
{
private:
    SingleNode* head_;
    size_t size_;
    bool isEmpty_;
public:
    Stack() : head_(nullptr), size_(0), isEmpty_(true) { std::cout << "Created empty Stack at " << this << std::endl; }
    Stack(SingleNode* initHead);
    ~Stack();

    // Methods
    void parse() const;
    void insert(int newData);
    void insert(SingleNode* newNode);
    void pop();
    SingleNode* peek() const { return this->head_; }

    // Getters
    size_t getSize() const { return this->size_; }
    bool isEmpty() const { return this->isEmpty_; }
};

#endif