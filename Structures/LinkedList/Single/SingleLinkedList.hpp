#ifndef STRUCTURES_LINKED_LIST_SINGLE_SINGLE_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_SINGLE_SINGLE_LINKED_LIST_H
#include <vector>

#include "../../Common/Node/Node.hpp"
#include "../LinkedList.hpp"

namespace SingleLinked
{
    class List : public LinkedList
    {
    private:
        Node* head_;
    public:
        List() : LinkedList(0, false), head_(nullptr) {}
        List(int initValue) : List(new Node(initValue)) {}
        List(Node* initHead);
        ~List();

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
        void insertHead(Node* newNode);
        void pushBack(Node* newNode);
        void insertAt(Node* newNode, const size_t& pos);
    };
} // namespace SingleLinked
#endif
