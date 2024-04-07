#include <iostream>

#include "./Stack.hpp"

Stack::Stack(Node* initHead)
{
    if(!initHead)
    {
        std::cout << "Created stack object with head at nullptr\n";
        this->isEmpty_ = true;
        this->size_ = 0;
        return;
    }

    this->head_ = initHead;
    this->size_ = Node::calculateNodeLenght(initHead);
    this->isEmpty_ = false;
    std::cout << "Created stack object with params: head_=" << this->head_ << " size_=" << this->size_ << " isEmpty_=" << this->isEmpty_ << std::endl;
}

Stack::~Stack()
{
    std::cout << "Deleting stack from " << this << " with head at " << this->head_ << "\n";
    Node* helper = this->head_;
    // Maybe change to pop later?
    while(helper)
    {
        Node* nextNode = helper->getNext();
        delete(helper);
        helper = nextNode;
        --this->size_;
    }
    this->isEmpty_ = true;
    std::cout << "Stack entry deleted" << std::endl;
}

void Stack::parse() const
{
    std::cout << "Printing " << this << " with head at " << this->head_ << "\n";
    Node* helper = this->head_;
    while(helper)
    {
        std::cout << "At " << helper << " with params: data_=" << helper->getData() << " next_=" << helper->getNext() <<  "\n";
        helper = helper->getNext();
    }
    std::cout << "Parsing done" << std::endl;
}

void Stack::insert(int newData)
{
    Node* makeNode = new Node(newData);
    this->insert(makeNode);
}

void Stack::insert(Node* newNode)
{
    std::cout << "Adding new node at " << newNode << " to stack at " << this << "\n";
    if(!this->head_)
    {
        this->head_ = newNode;
        isEmpty_ = false;
    }
    else
    {
        newNode->setNext(this->head_);
        this->head_ = newNode;
    }

    ++this->size_;
    std::cout << "Value " << newNode->getData() << " added successfully" << std::endl;
    return;
}

void Stack::pop()
{
    if(this->isEmpty_ || !this->head_)
    {
        std::cout << "Stack at " << this << " is empty.\n";
        return;
    }

    std::cout << "Popping value from stack (" << this << ") current top at " << this->head_ << "\n";
    Node* prevHead = this->head_;
    this->head_ = prevHead->getNext();
    delete(prevHead);
    --this->size_;
    if(!this->size_) this->isEmpty_ = false;
    std::cout << "Value popped" << std::endl;
}