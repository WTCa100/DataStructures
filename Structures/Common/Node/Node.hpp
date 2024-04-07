#ifndef STRUCTURES_COMMON_NODE_H
#define STRUCTURES_COMMON_NODE_H

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned long size_t;
#endif

// Maybe changed later into class template to make it more unique.

class Node
{
private:
    int data_;
    Node* next_;
public:
    Node() : Node(0) {};
    Node(int initData) : data_(initData), next_(nullptr) {}

    // Setter
    void setData(int newData) { this->data_ = newData; }
    void setNext(Node* newNext) { this->next_ = newNext; }
    // Getter
    int getData() const { return this->data_; }
    Node* getNext() const { return this->next_; } 

    // Methods
    static size_t calculateNodeLenght(const Node* target);

    ~Node() = default;
};

#endif