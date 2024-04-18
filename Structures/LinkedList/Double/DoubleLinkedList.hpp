#ifndef STRUCTURES_LINKED_LIST_DOUBLE_DOUBLE_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_DOUBLE_DOUBLE_LINKED_LIST_H

#include <vector>
#include "../LinkedList.hpp"
#include "../../Common/Node/DoubleNode.hpp"

class DoubleLinkedList : public LinkedList
{
    private:
    DoubleNode* head_;
    public:
    DoubleLinkedList() : LinkedList(0, false), head_(nullptr) {}
    DoubleLinkedList(int initValue) : DoubleLinkedList(new DoubleNode(initValue)) {}
    DoubleLinkedList(DoubleNode* initHead);
    ~DoubleLinkedList();

    // Implementations
    void popHead() override;
    void popBack() override;
    void popAt(const size_t& pos) override;
    void insertHead(const int& newValue) override;
    void pushBack(const int& newValue) override;
    void insertAt(const int& newValue, const size_t& pos) override;
    bool isPresent(const int& value) const override;
    void parse() const override;

    // Getters
    int at(const size_t& pos) override;
    std::vector<int> getValues() override;
    // Derrived methods
    void insertHead(DoubleNode* newNode);
    void pushBack(DoubleNode* newNode);
    void insertAt(DoubleNode* newNode, const size_t& pos);
};
#endif
