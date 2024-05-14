#include <iostream>

#include "../Common/Utilities/Utilities.hpp"
#include "./Stack.hpp"


template <typename T>
Stack<T>::Stack(SingleNode<T>* initHead)
{
    if(!initHead)
    {
        std::cout << "Created stack object with head at nullptr\n";
        isEmpty_ = true;
        size_ = 0;
        return;
    }

    head_ = initHead;
    size_ = Utilities::calculateNodeSequenceLenght(initHead);
    isEmpty_ = false;
    std::cout << "Created stack object with params: head_=" << head_ << " size_=" << size_ << " isEmpty_=" << isEmpty_ << std::endl;
}

template <typename T>
Stack<T>::~Stack()
{
    std::cout << "Deleting stack from " << this << " with head at " << head_ << "\n";
    SingleNode<T>* helper = head_;
    // Maybe change to pop later?
    while(helper)
    {
        SingleNode<T>* nextNode = helper->getNext();
        delete(helper);
        helper = nextNode;
        --size_;
    }
    isEmpty_ = true;
    std::cout << "Stack entry deleted" << std::endl;
}

template <typename T>
void Stack<T>::parse() const
{
    std::cout << "Printing " << this << " with head at " << head_ << "\n";
    SingleNode<T>* helper = head_;
    while(helper)
    {
        std::cout << "At " << helper << " with params: data_=" << helper->getData() << " next_=" << helper->getNext() <<  "\n";
        helper = helper->getNext();
    }
    std::cout << "Parsing done" << std::endl;
}

template <typename T>
void Stack<T>::insert(const T& newData)
{
    SingleNode<T>* makeNode = new SingleNode<T>(newData);
    insert(makeNode);
}

template <typename T>
void Stack<T>::insert(SingleNode<T>* newNode)
{
    std::cout << "Adding new node at " << newNode << " to stack at " << this << "\n";
    if(!head_)
    {
        head_ = newNode;
        isEmpty_ = false;
    }
    else
    {
        newNode->setNext(head_);
        head_ = newNode;
    }

    ++size_;
    std::cout << "Value " << newNode->getData() << " added successfully" << std::endl;
    return;
}

template <typename T>
void Stack<T>::pop()
{
    if(isEmpty_ || !head_)
    {
        std::cout << "Stack at " << this << " is empty.\n";
        return;
    }

    std::cout << "Popping value from stack (" << this << ") current top at " << head_ << "\n";
    SingleNode<T>* prevHead = head_;
    head_ = prevHead->getNext();
    delete(prevHead);
    --size_;
    if(!size_) isEmpty_ = false;
    std::cout << "Value popped" << std::endl;
}