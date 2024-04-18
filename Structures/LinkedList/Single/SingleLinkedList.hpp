#ifndef STRUCTURES_LINKED_LIST_SINGLE_SINGLE_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_SINGLE_SINGLE_LINKED_LIST_H
#include <vector>

#include "../../Common/Node/SingleNode.hpp"
#include "../LinkedList.hpp"

class SingleLinkedList : public LinkedList
{
private:
    SingleNode* head_;
public:
    SingleLinkedList() : LinkedList(0, false), head_(nullptr) {}
    SingleLinkedList(int initValue) : SingleLinkedList(new SingleNode(initValue)) {}
    SingleLinkedList(SingleNode* initHead);
    ~SingleLinkedList();

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
    // Derriveds' methods
    void insertHead(SingleNode* newNode);
    void pushBack(SingleNode* newNode);
    void insertAt(SingleNode* newNode, const size_t& pos);
};

#endif
