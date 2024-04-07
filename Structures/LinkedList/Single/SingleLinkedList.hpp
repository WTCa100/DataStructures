#pragma once
#include <vector>

#include "../../Common/Node/Node.hpp"

class SingleLinkedList
{
private:
    Node* head_;
    size_t size_;
    bool isEmpty_;
public:
    SingleLinkedList() : head_(nullptr), size_(0), isEmpty_(true) {}
    SingleLinkedList(int initValue) : SingleLinkedList(new Node(initValue)) {}
    SingleLinkedList(Node* initHead);
    ~SingleLinkedList();

    // Methods
    void popHead();
    void popBack();
    void popAt(const size_t& pos);
    void insertHead(const int& newValue);
    void insertHead(Node* newNode);
    void pushBack(const int& newValue);
    void pushBack(Node* newNode);
    void insertAt(const int& newValue, const size_t& pos);
    void insertAt(Node* newNode, const size_t& pos);
    bool isPresent(const int& value);
    void parse() const;

    // Getters
    bool isEmpty() { return this->isEmpty_; }
    size_t getSize() { return this->size_; }
    bool at(const size_t& pos, int& container);
    std::vector<int> getValues();

};
