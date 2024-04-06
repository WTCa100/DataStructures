#ifndef STRUCTURES_COMMON_NODE_H
#define STRUCTURES_COMMON_NODE_H

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

    ~Node() = default;
};

#endif