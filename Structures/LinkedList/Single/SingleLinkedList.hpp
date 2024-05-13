#ifndef STRUCTURES_LINKED_LIST_SINGLE_SINGLE_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_SINGLE_SINGLE_LINKED_LIST_H
#include <vector>

#include "../../Common/Node/SingleNode.hpp"
#include "../LinkedList.hpp"

template <typename T>
class SingleLinkedList : public LinkedList
{
private:
    SingleNode* head_;
public:
    SingleLinkedList() : LinkedList(0, true), head_(nullptr) {}
    SingleLinkedList(T initValue) : SingleLinkedList(new SingleNode<T>(initValue)) {}
    SingleLinkedList(SingleNode<T>* initHead);
    ~SingleLinkedList();

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
    std::vector<int> getValues() override;
    // Derriveds' methods
    void insertHead(SingleNode<T>* newNode);
    void pushBack(SingleNode<T>* newNode);
    void insertAt(SingleNode<T>* newNode, const size_t& pos);
};

#endif
