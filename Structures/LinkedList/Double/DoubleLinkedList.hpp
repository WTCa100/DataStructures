#ifndef STRUCTURES_LINKED_LIST_DOUBLE_DOUBLE_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_DOUBLE_DOUBLE_LINKED_LIST_H

#include <vector>
#include "../LinkedList.hpp"
#include "../../Common/Node/DoubleNode.hpp"

template <typename T>
class DoubleLinkedList : public LinkedList
{
    private:
    DoubleNode<T>* head_;
    public:
    DoubleLinkedList() : LinkedList(0, true), head_(nullptr) {}
    DoubleLinkedList(T initValue) : DoubleLinkedList(new DoubleNode<T>(initValue)) {}
    DoubleLinkedList(DoubleNode<T>* initHead);
    ~DoubleLinkedList();

    // Implementations
    void popHead() override;
    void popBack() override;
    void popAt(const size_t& pos) override;
    void insertHead(const int& newValue) override;
    void pushBack(const T& newValue) override;
    void insertAt(const T& newValue, const size_t& pos) override;
    bool isPresent(const T& value) const override;
    void parse() const override;

    // Getters
    T at(const size_t& pos) override;
    std::vector<T> getValues() override;
    // Derrived methods
    void insertHead(DoubleNode<T>* newNode);
    void pushBack(DoubleNode<T>* newNode);
    void insertAt(DoubleNode<T>* newNode, const size_t& pos);
};
#endif
