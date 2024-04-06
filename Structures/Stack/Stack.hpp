#pragma once

#include "../Common/Node/Node.hpp"

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned long size_t;
#endif

class Stack
{
private:
    Node* head_;
    size_t size_;
    bool isEmpty_;
    size_t calculateSize();
public:
    Stack() : head_(nullptr), size_(0), isEmpty_(true) { std::cout << "Created empty Stack at " << this << std::endl; }
    Stack(Node* initHead);
    ~Stack();

    // Methods
    void parse() const;
    void insert(int newData);
    void insert(Node* newNode);
    void pop();
    Node* peek() const { return this->head_; }

    // Getters
    size_t getSize() const { return this->size_; }
    bool isEmpty() const { return this->isEmpty_; }
};