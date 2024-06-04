#ifndef STRUCTURES_LINKED_LIST_SINGLE_SINGLE_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_SINGLE_SINGLE_LINKED_LIST_H

#include <vector>
#include "../../Common/Node/SingleNode.hpp"
#include "../LinkedList.hpp"

#define DBG_MODE

template <typename T>
class SingleLinkedList : public LinkedList<T>
{
private:
    SingleNode<T>* head_;
public:
    SingleLinkedList() : LinkedList<T>(0, true), head_(nullptr) {}
    SingleLinkedList(T initValue) : SingleLinkedList(new SingleNode<T>(initValue)) {}
    SingleLinkedList(SingleNode<T>* initHead);
    ~SingleLinkedList();

    // Implementations
    void popHead() override;
    void popBack() override;
    void popAt(const size_t& pos) override;
    void insertHead(const T& newValue) override;
    void pushBack(const T& newValue) override;
    void insertAt(const T& newValue, const size_t& pos) override;
    bool isPresent(const T& value) const override;
    void parse() const override;

    // Getters
    T at(const size_t& pos) override;
    std::vector<T> getValues() override;
    // Derriveds' methods
    void insertHead(SingleNode<T>* newNode);
    void pushBack(SingleNode<T>* newNode);
    void insertAt(SingleNode<T>* newNode, const size_t& pos);
};

template <typename T>
SingleLinkedList<T>::SingleLinkedList(SingleNode<T>* initHead) : LinkedList<T>(Utilities::calculateNodeSequenceLenght(initHead), false)
{
    if(!initHead)
    {
        std::cout << "Created Single Linked List object with head at nullptr\n";
        this->isEmpty_ = true;
        this->size_ = 0;
        return;
    }
    head_ = initHead;
    std::cout << "Created Single Linked List object with params: head_=" << head_ << " size_=" << this->size_ << " isEmpty_=" << this->isEmpty_ << std::endl;
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    std::cout << "Tearing down Single Linked List " << this << " with head at " << head_ << "\n";

    SingleNode<T>* helper = head_;
    if(!this->isEmpty())
    {
        while(helper)
        {
            SingleNode<T>* nextNode = helper->getNext();
            delete(helper);
            helper = nextNode;
            --this->size_;
        }
        this->isEmpty_ = true;
    }
    std::cout << "Teardown successful" << std::endl;
}

template <typename T>
void SingleLinkedList<T>::popHead()
{
    if(this->isEmpty_ || !head_)
    {
        std::cout << "Single Linked List at " << this << " is empty or head is null\n";
        return;
    }

    std::cout << "Deleting head at Single Linked List " << this << " with data_=" << head_->getData() << "\n";
    T deletedNodeData = head_->getData();
    if(!head_->getNext())
    {
        delete(head_);
        head_ = nullptr;
    }
    else
    {
        SingleNode<T>* currentHead = head_;
        head_ = currentHead->getNext();
        delete(currentHead);
    }
    #ifdef DBG_MODE
    std::cout << "Successufuly deleted head (data = " << deletedNodeData << ") from Single Linked List\n";
    #endif
    if(head_)
    {
        std::cout << "New head at " << head_ << " (data = " << head_->getData() << " next = " << head_->getNext() << ")" << std::endl;  
    }
    --this->size_;
    if(!this->size_) this->isEmpty_ = true;
}

template <typename T>
void SingleLinkedList<T>::popBack()
{
    if(this->isEmpty_ || !head_)
    {
        std::cout << "Single Linked List at " << this << " is empty or head is null\n";
        return;
    }

    std::cout << "Deleting back at Single Linked List " << this << "\n";
    T deletedNodeData;
    SingleNode<T>* prev   = head_;
    SingleNode<T>* last   = head_->getNext();
    while(last->getNext())
    {
        prev = last;
        last = prev->getNext();
    }
    // [Prev] -> [Helper - Valid Node] -> Null
    prev->setNext(nullptr);
    std::cout << "Last value " << last << " with: data_ " << last->getData() << "\n"; 
    if(prev == head_) // we haven't move so we will front = back
    {
        last = prev;
    }
    deletedNodeData = last->getData();
    delete(last);
    // [Prev] -> Null
    #ifdef DBG_MODE
    std::cout << "Successfuly deleted last element (data = " << deletedNodeData << ") in a Single Linked List" << std::endl;
    #endif
    --this->size_;
    if(!this->size_) this->isEmpty_ = true;
}

template <typename T>
void SingleLinkedList<T>::popAt(const size_t& pos)
{
    if(this->isEmpty_ || !head_)
    {
        std::cout << "Single Linked List at " << this << " is empty or head is null\n";
        return;
    }

    if(pos >= this->size_)
    {
        std::cout << "Given index is out of range in Single Linked List at " << this << "\n";
        return;
    }

    if(pos == 0) popHead();
    else if (pos == this->size_ - 1) popBack();
    else
    {
        T deletedNodeData;
        SingleNode<T>* prev = head_;
        SingleNode<T>* target = prev->getNext();
        size_t index = 1;
        while(index < pos)
        {
            prev = target;
            target = prev->getNext();
            ++index;
        }

        deletedNodeData = target->getData();
        // [Prev] -> [Target] -> [Next] -> ... -> Null
        prev->setNext(target->getNext());
        delete(target);
        // [Prev] -> [Next] -> ... -> Null
        std::cout << "Successfuly deleted element (data = " << deletedNodeData << ") at index " << index << " in a Single Linked List" << std::endl;
        --this->size_;
        if(!this->size_) this->isEmpty_ = true;
    }
}

template <typename T>
void SingleLinkedList<T>::insertHead(const T& newValue)
{
    insertHead(new SingleNode<T>(newValue));
}

template <typename T>
void SingleLinkedList<T>::insertHead(SingleNode<T>* newNode)
{
    std::cout << "Adding new node " << newNode << " as head with data_=" << newNode->getData() << 
                " at Single Linked List " << this << " current head at " << head_ << "\n";
    if(!head_ || this->isEmpty_)
    {
        head_ = newNode;
        this->size_ = Utilities::calculateNodeSequenceLenght(head_);
        this->isEmpty_ = false;
    }
    else
    {
        newNode->setNext(head_);
        head_ = newNode;
        ++this->size_;
    }
    std::cout << "New head added to Single Linked List. Current head at " << head_ << std::endl; 
}

template <typename T>
void SingleLinkedList<T>::pushBack(const T& newValue)
{
    pushBack(new SingleNode<T>(newValue));
}

template <typename T>
void SingleLinkedList<T>::pushBack(SingleNode<T>* newNode)
{
    std::cout << "Adding new node " << newNode << " as back with data_=" << newNode->getData() << 
                " at Single Linked List " << this << "\n";
    if(!head_ || this->isEmpty_)
    {
        head_ = newNode;
        this->isEmpty_ = false;
    }
    else
    {
        SingleNode<T>* last = head_;
        while(last->getNext())
        {
            last = last->getNext();
        }
        last->setNext(newNode);
        // We can technically push back a node with existing sequence
        this->size_ = Utilities::calculateNodeSequenceLenght(newNode);
    }
    this->size_ = Utilities::calculateNodeSequenceLenght(head_);
    std::cout << "New back added to Single Linked List. Current head at " << head_ << std::endl; 
}

template <typename T>
void SingleLinkedList<T>::insertAt(const T& newValue, const size_t& pos)
{
    insertAt(new SingleNode<T>(newValue), pos);
}

template <typename T>
void SingleLinkedList<T>::insertAt(SingleNode<T>* newNode, const size_t& pos)
{
    if(!head_ || this->isEmpty_)
    {
        std::cout << "Single Linked List at " << this << " is empty or head is null\n";
    }
    else if(pos >= this->size_)
    {
        std::cout << pos << " is out of range in Single Linked List at " << this << " Aborting..." << std::endl;
        return;
    }

    if((!head_ || this->isEmpty_) || pos == 0) insertHead(newNode);
    else
    {
        std::cout << "Adding " << newNode << " with data_=" << newNode->getData() << " at " << this << " pos " << pos << "\n";
        SingleNode<T>* prev = head_;
        SingleNode<T>* currentIndexNode = prev->getNext();
        size_t index = 0;
        while(index < pos - 1)
        {
            prev = currentIndexNode;
            currentIndexNode = prev->getNext();
            ++index;
        }

        // Pos: N, [New Node N, k]
        // [Node N - 1, x] -> [Node N, y] -> [Node N + 1, z]
        // Here currentIndexPos is located at the desired position.
        // Prev shall now change it's next poitner to the newNode and newNode change it to the currentIndexNode
        prev->setNext(newNode);
        newNode->setNext(currentIndexNode);
        ++this->size_;
        // [Node N - 1, x] -> [Node N, k] -> [Node N + 1, y] -> [Node, N + 2,  z] 
    }
    std::cout << "Successfuly added new value into a Single Linked List" << std::endl;
}

template <typename T>
bool SingleLinkedList<T>::isPresent(const T& value) const
{
    if(!head_ || this->isEmpty_)
    {
        std::cout << "Single Linked List at " << this << " is empty or head is null\n";
        return false;
    }

    SingleNode<T>* ptr  = head_;
    while(ptr)
    {
        if(ptr->getData() == value)
        {
            std::cout << "Value found at " << ptr << std::endl;
            return true;
        }
        ptr = ptr->getNext();
    }

    std::cout << "Value not found" << std::endl;
    return false;
}

template <typename T>
void SingleLinkedList<T>::parse() const
{
    if(!head_ || this->isEmpty_)
    {
        std::cout << "Single Linked List at " << this << " is empty or head is null\n";
        return;
    }

    SingleNode<T>* helper = head_;
    std::cout << "Parsing Single Linked List at " << this << " with head at " << head_ << "\n";
    while(helper)
    {
        std::cout << "At " << helper << " with params: data_=" << helper->getData() << " next_=" << helper->getNext() <<  "\n";
        helper = helper->getNext();
    }
    std::cout << "Parsing done" << std::endl;
}

template <typename T>
T SingleLinkedList<T>::at(const size_t& pos)
{
    std::stringstream errMsg("");
    if(!head_ || this->isEmpty_)
    {
        errMsg << "Single Linked List at " << this << " is empty or head is null";
        throw std::runtime_error(errMsg.str().c_str());
    }
    if(pos >= this->size_)
    {
        // Can also be changed into a throw
        errMsg << pos << " is out of range in Single Linked List at " << this << " Aborting...";
        throw std::out_of_range(errMsg.str().c_str());
    }

    SingleNode<T>* ptr = head_;
    size_t index = 0;

    while(index < pos)
    {
        ptr = ptr->getNext();
        ++index;
    }

    return ptr->getData();
}

template <typename T>
std::vector<T> SingleLinkedList<T>::getValues()
{
    std::vector<T> out;
    SingleNode<T>* ptr = head_;
    while(ptr)
    {
        out.push_back(ptr->getData());
        ptr = ptr->getNext();
    }
    return out;
}
#endif
