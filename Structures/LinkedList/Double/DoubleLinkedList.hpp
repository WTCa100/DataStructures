#ifndef STRUCTURES_LINKEDLIST_DOUBLELINKEDLIST_H
#define STRUCTURES_LINKEDLIST_DOUBLELINKEDLIST_H

#include <vector>
#include "../LinkedList.hpp"
#include "../../Common/Node/DoubleNode.hpp"

template <typename T>
class DoubleLinkedList : public LinkedList<T>
{
    private:
    DoubleNode<T>* head_;
    public:
    DoubleLinkedList() : LinkedList<T>(0, true), head_(nullptr) {}
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

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleNode<T>* initHead) : LinkedList<T>(Utilities::calculateNodeSequenceLenght(initHead), false)
{
    if(initHead->getPrev())
    {
        std::stringstream errMsg("");
        errMsg << "initHead->prev_ shall not contain any value.\n";
        throw std::runtime_error(errMsg.str().c_str()); 
    };

    if(!initHead)
    {
        std::cout << "Created Double Linked List object with head at nullptr\n";
        this->isEmpty_ = true;
        this->size_ = 0;
        return;
    }
    head_ = initHead;
    std::cout << "Created Double Linked List object with params: head_=" << head_ << " size_=" << this->size_ << " isEmpty_=" << this->isEmpty_ << std::endl;
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    std::cout << "Tearing down Double Linked List " << this << " with head at " << head_ << "\n";

    DoubleNode<T>* helper = head_;
    if(!this->isEmpty_)
    {
        while(helper)
        {
            // Debug entry
            std::cout  << "DBG: Tearing down " << helper << "\n";
            DoubleNode<T>* nextNode = helper->getNext();
            delete(helper);
            helper = nextNode;
            --this->size_;
        }
        this->isEmpty_ = true;
    }
    std::cout << "Teardown successful" << std::endl;
}

template <typename T>
void DoubleLinkedList<T>::popHead()
{
    if(!head_ || this->isEmpty_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
        return;
    }

    std::cout << "Deleting head at Double Linked List " << this << " with data_=" << head_->getData() << "\n";
    T deletedNodeData = head_->getData();
    // We do only one check, as head shall not have any pointer to it's previous sibling
    if(!head_->getNext())
    {
        delete(head_);
        // Avoid invalid read-size block during the next display handling
        head_ = nullptr;
    }
    else
    {
        DoubleNode<T>* currentHead = head_;
        head_ = currentHead->getNext();
        head_->setPrev(nullptr); // No prev is allowed as head
        delete(currentHead);
    }
    std::cout << "Successufuly deleted head (data = " << deletedNodeData << ") from Double Linked List\n";
    if(head_)
    {
        std::cout << "New head at " << head_ << " (data = " << head_->getData() << " next = " << head_->getNext() << ")" << std::endl;  
    }
    --this->size_;
    if(!this->size_) this->isEmpty_ = true;
}

template <typename T>
void DoubleLinkedList<T>::popBack()
{
    if(this->isEmpty_ || !head_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
        return;
    }

    std::cout << "Deleting back at Double Linked List " << this << "\n";
    int deletedNodeData;
    DoubleNode<T>* last   = head_;
    while(last->getNext())
    {
        last = last->getNext();
    }
    /*
    +------+ --> +--------+     +------+
    | prev |     | target | --> | NULL |
    +------+ <-- +--------+     +------+
    */
   if(!(last == head_))
   {
        last->getPrev()->setNext(nullptr);
        std::cout << "DBG: Prev " << last->getPrev() << " with: data_ " << last->getPrev()->getData() << "\n";
   }
    std::cout << "Last value " << last << " with: data_ " << last->getData() << "\n"; 
    deletedNodeData = last->getData();
    delete(last);
    /*
    +------+     +------+
    | prev | --> | NULL |
    +------+     +------+
    */
    std::cout << "Successfuly deleted last element (data = " << deletedNodeData << ") in a Double Linked List" << std::endl;
    --this->size_;
    if(!this->size_) this->isEmpty_ = true;
}

template <typename T>
void DoubleLinkedList<T>::popAt(const size_t& pos)
{
    if(this->isEmpty_ || !head_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
        return;
    }

    if(pos >= this->size_)
    {
        std::cout << "Given index is out of range in Double Linked List at " << this << "\n";
        return;
    }

    if(pos == 0) popHead();
    else if (pos == this->size_ - 1) popBack();
    else
    {
        T deletedNodeData;
        DoubleNode<T>* target = head_->getNext();
        size_t index = 1;
        while(index < pos)
        {
            target = target->getNext();
            ++index;
        }

        deletedNodeData = target->getData();
        /*
        +------+ --> +--------+ --> +------+ --> +------+     +------+ 
        | prev |     | target |     | next |     | .... | --> | NULL | 
        +------+ <-- +--------+ <-- +------+ <-- +------+     +------+ 
        */
        target->getPrev()->linkNext(target->getNext());
        delete(target);
        /*
        +------+ --> +------+ --> +------+     +------+ 
        | prev |     | next |     | .... | --> | NULL | 
        +------+ <-- +------+ <-- +------+     +------+ 
        */
        std::cout << "Successfuly deleted element (data = " << deletedNodeData << ") at index " << index << " in a Single Linked List" << std::endl;
        --this->size_;
        if(!this->size_) this->isEmpty_ = true;
    }
}

template <typename T>
void DoubleLinkedList<T>::insertHead(const int& newValue)
{
    insertHead(new DoubleNode<T>(newValue));
}

template <typename T>
void DoubleLinkedList<T>::insertHead(DoubleNode<T>* newNode)
{
    std::cout << "Adding new node " << newNode << " as head with data_=" << newNode->getData() << 
                " at Double Linked List " << this << " current head at " << head_ << "\n";

    if(newNode->getPrev())
    {
        std::cout << "Cannot insert a had that has a prev_ pointer." << std::endl;
        return;
    }

    if(!head_ || this->isEmpty_)
    {
        head_ = const_cast<DoubleNode<T>*>(newNode);
        this->size_ = Utilities::calculateNodeSequenceLenght(head_);
        this->isEmpty_ = false;
    }
    else
    {    
        newNode->linkNext(head_);
        head_ = newNode;
        ++this->size_;
    }
    std::cout << "New back added to Double Linked List. Current head at " << head_ << std::endl; 
}

template <typename T>
void DoubleLinkedList<T>::pushBack(const T& newValue)
{
    pushBack(new DoubleNode<T>(newValue));
}

template <typename T>
void DoubleLinkedList<T>::pushBack(DoubleNode<T>* newNode)
{
    std::cout << "Adding new node " << newNode << " as back with data_=" << newNode->getData() << 
                " at Double Linked List " << this << "\n";

    if(!head_ || this->isEmpty_)
    {
        if(newNode->getPrev())
        {
            std::cout << "Cannot insert a had that has a prev_ pointer." << std::endl;
            return;
        }
        head_ = newNode;
        this->isEmpty_ = false;
    }
    else
    {
        DoubleNode<T>* last = head_;
        while(last->getNext())
        {
            last = last->getNext();
        }
        last->linkNext(newNode);
    }

    this->size_ = Utilities::calculateNodeSequenceLenght(newNode);
    std::cout << "New back added to Double Linked List. Current head at " << head_ << std::endl; 
}

template <typename T>
void DoubleLinkedList<T>::insertAt(const T& newValue, const size_t& pos)
{
    insertAt(new DoubleNode<T>(newValue), pos);
}

template <typename T>
void DoubleLinkedList<T>::insertAt(DoubleNode<T>* newNode, const size_t& pos)
{
    if(!head_ || this->isEmpty_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
    }
    else if(pos >= this->size_)
    {
        std::cout << pos << " is out of range in Double Linked List at " << this << " Aborting..." << std::endl;
        return;
    }

    if((!head_ || this->isEmpty_) || pos == 0) insertHead(newNode);
    else
    {
        std::cout << "Adding " << newNode << " with data_=" << newNode->getData() << " at " << this << " pos " << pos << "\n";
        DoubleNode<T>* currentIndexNode = head_->getNext();
        size_t index = 1;
        while(index < pos)
        {
            currentIndexNode = currentIndexNode->getNext();
            ++index;
        }

        /*
        Pos: N, [New Node N, k]
        +------------+ --> +----------+ --> +------------+ 
        | Node N - 1 |     | Node N   |     | Node N + 1 |  
        |  Value: x  |     | Value: y |     |  Value: z  |
        +------------+ <-- +----------+ <-- +------------+ 
        Here currentIndexPos is located at the desired position.
        Prev shall now change it's next poitner to the newNode and newNode change it to the currentIndexNode
        */
        currentIndexNode->getPrev()->linkNext(newNode);
        newNode->linkNext(currentIndexNode);
        ++this->size_;
        /*
        +------------+ --> +----------+ --> +------------+ --> +------------+ 
        | Node N - 1 |     | Node N   |     | Node N + 1 |     | Node N + 2 |  
        |  Value: x  |     | Value: k |     | Value: y   |     | Value: z   |
        +------------+ <-- +----------+ <-- +------------+ <-- +------------+ 
        */
    }
    std::cout << "Successfuly added new value into a Double Linked List" << std::endl;
}

template <typename T>
bool DoubleLinkedList<T>::isPresent(const T& value) const
{
    if(!head_ || this->isEmpty_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
        return false;
    }

    DoubleNode<T>* ptr = head_;
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
void DoubleLinkedList<T>::parse() const
{
    if(!head_ || this->isEmpty_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
        return;
    }

    DoubleNode<T>* helper = head_;
    std::cout << "Parsing Double Linked List at " << this << " with head at " << head_ << "\n";
    while(helper)
    {
        std::cout << "At " << helper << " with params: data_=" << helper->getData() 
                  << " prev_=" << helper->getPrev() << " next_=" << helper->getNext() << "\n";
        helper = helper->getNext();
    }
    std::cout << "Parsing done" << std::endl;
}

template <typename T>
T DoubleLinkedList<T>::at(const size_t& pos)
{
    std::stringstream errMsg("");
    if(!head_ || this->isEmpty_)
    {
        errMsg << "Double Linked List at " << this << " is empty or head is null";
        throw std::runtime_error(errMsg.str().c_str());
    }
    if(pos >= this->size_)
    {
        // Can also be changed into a throw
        errMsg << pos << " is out of range in Double Linked List at " << this << " Aborting...";
        throw std::out_of_range(errMsg.str().c_str());
    }

    DoubleNode<T>* ptr = head_;
    size_t index = 0;

    while(index < pos)
    {
        ptr = ptr->getNext();
        ++index;
    }

    return ptr->getData();
}

template <typename T>
std::vector<T> DoubleLinkedList<T>::getValues()
{
    std::vector<T> out;
    DoubleNode<T>* ptr = head_;
    while(ptr)
    {
        out.push_back(ptr->getData());
        ptr = ptr->getNext();
    }
    return out;
}
#endif
