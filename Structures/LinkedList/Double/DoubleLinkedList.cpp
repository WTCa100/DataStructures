#include <iostream>
#include <sstream>

#include "../../Common/Utilities/Utilities.hpp"
#include "DoubleLinkedList.hpp"


DoubleLinkedList::DoubleLinkedList(DoubleNode* initHead) : LinkedList(Utilities::calculateNodeSequenceLenght(initHead), false)
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
    this->head_ = initHead;
    std::cout << "Created Double Linked List object with params: head_=" << this->head_ << " size_=" << this->size_ << " isEmpty_=" << this->isEmpty_ << std::endl;
}

DoubleLinkedList::~DoubleLinkedList()
{
    std::cout << "Tearing down Double Linked List " << this << " with head at " << this->head_ << "\n";

    DoubleNode* helper = this->head_;
    if(!this->isEmpty_)
    {
        while(helper)
        {
            // Debug entry
            std::cout  << "DBG: Tearing down " << helper << "\n";
            DoubleNode* nextNode = helper->getNext();
            delete(helper);
            helper = nextNode;
            --this->size_;
        }
        this->isEmpty_ = true;
    }
    std::cout << "Teardown successful" << std::endl;
}

void DoubleLinkedList::popHead()
{
    if(!this->head_ || this->isEmpty_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
        return;
    }

    std::cout << "Deleting head at Double Linked List " << this << " with data_=" << this->head_->getData() << "\n";
    int deletedNodeData = this->head_->getData();
    // We do only one check, as head shall not have any pointer to it's previous sibling
    if(!head_->getNext())
    {
        delete(head_);
        // Avoid invalid read-size block during the next display handling
        head_ = nullptr;
    }
    else
    {
        DoubleNode* currentHead = this->head_;
        this->head_ = currentHead->getNext();
        this->head_->setPrev(nullptr); // No prev is allowed as head
        delete(currentHead);
    }
    std::cout << "Successufuly deleted head (data = " << deletedNodeData << ") from Double Linked List\n";
    if(this->head_)
    {
        std::cout << "New head at " << this->head_ << " (data = " << this->head_->getData() << " next = " << this->head_->getNext() << ")" << std::endl;  
    }
    --this->size_;
    if(!this->size_) this->isEmpty_ = true;
}

void DoubleLinkedList::popBack()
{
    if(this->isEmpty_ || !this->head_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
        return;
    }

    std::cout << "Deleting back at Double Linked List " << this << "\n";
    int deletedNodeData;
    DoubleNode* last   = this->head_;
    while(last->getNext())
    {
        last = last->getNext();
    }
    /*
    +------+ --> +--------+     +------+
    | prev |     | target | --> | NULL |
    +------+ <-- +--------+     +------+
    */
   if(!(last == this->head_))
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

void DoubleLinkedList::popAt(const size_t& pos)
{
    if(this->isEmpty_ || !this->head_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
        return;
    }

    if(pos >= this->size_)
    {
        std::cout << "Given index is out of range in Double Linked List at " << this << "\n";
        return;
    }

    if(pos == 0) this->popHead();
    else if (pos == this->size_ - 1) this->popBack();
    else
    {
        int deletedNodeData;
        DoubleNode* target = this->head_->getNext();
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

void DoubleLinkedList::insertHead(const int& newValue)
{
    this->insertHead(new DoubleNode(newValue));
}

void DoubleLinkedList::insertHead(DoubleNode* newNode)
{
    std::cout << "Adding new node " << newNode << " as head with data_=" << newNode->getData() << 
                " at Double Linked List " << this << " current head at " << this->head_ << "\n";

    if(newNode->getPrev())
    {
        std::cout << "Cannot insert a had that has a prev_ pointer." << std::endl;
        return;
    }

    if(!this->head_ || this->isEmpty_)
    {
        this->head_ = const_cast<DoubleNode*>(newNode);
        this->size_ = Utilities::calculateNodeSequenceLenght(this->head_);
        this->isEmpty_ = false;
    }
    else
    {    
        newNode->linkNext(this->head_);
        this->head_ = newNode;
        ++this->size_;
    }
    std::cout << "New back added to Double Linked List. Current head at " << this->head_ << std::endl; 
}

void DoubleLinkedList::pushBack(const int& newValue)
{
    this->pushBack(new DoubleNode(newValue));
}

void DoubleLinkedList::pushBack(DoubleNode* newNode)
{
    std::cout << "Adding new node " << newNode << " as back with data_=" << newNode->getData() << 
                " at Double Linked List " << this << "\n";

    if(!this->head_ || this->isEmpty_)
    {
        if(newNode->getPrev())
        {
            std::cout << "Cannot insert a had that has a prev_ pointer." << std::endl;
            return;
        }
        this->head_ = newNode;
        this->isEmpty_ = false;
    }
    else
    {
        DoubleNode* last = this->head_;
        while(last->getNext())
        {
            last = last->getNext();
        }
        last->linkNext(newNode);
    }

    this->size_ = Utilities::calculateNodeSequenceLenght(newNode);
    std::cout << "New back added to Double Linked List. Current head at " << this->head_ << std::endl; 
}

void DoubleLinkedList::insertAt(const int& newValue, const size_t& pos)
{
    this->insertAt(new DoubleNode(newValue), pos);
}

void DoubleLinkedList::insertAt(DoubleNode* newNode, const size_t& pos)
{
    if(!this->head_ || this->isEmpty_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
    }
    else if(pos >= this->size_)
    {
        std::cout << pos << " is out of range in Double Linked List at " << this << " Aborting..." << std::endl;
        return;
    }

    if((!this->head_ || this->isEmpty_) || pos == 0) this->insertHead(newNode);
    else
    {
        std::cout << "Adding " << newNode << " with data_=" << newNode->getData() << " at " << this << " pos " << pos << "\n";
        DoubleNode* currentIndexNode = this->head_->getNext();
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

bool DoubleLinkedList::isPresent(const int& value) const
{
    if(!this->head_ || this->isEmpty_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
        return false;
    }

    DoubleNode* ptr = this->head_;
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

void DoubleLinkedList::parse() const
{
    if(!this->head_ || this->isEmpty_)
    {
        std::cout << "Double Linked List at " << this << " is empty or head is null\n";
        return;
    }

    DoubleNode* helper = this->head_;
    std::cout << "Parsing Double Linked List at " << this << " with head at " << this->head_ << "\n";
    while(helper)
    {
        std::cout << "At " << helper << " with params: data_=" << helper->getData() 
                  << " prev_=" << helper->getPrev() << " next_=" << helper->getNext() << "\n";
        helper = helper->getNext();
    }
    std::cout << "Parsing done" << std::endl;
}

int DoubleLinkedList::at(const size_t& pos)
{
    std::stringstream errMsg("");
    if(!this->head_ || this->isEmpty_)
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

    DoubleNode* ptr = this->head_;
    size_t index = 0;

    while(index < pos)
    {
        ptr = ptr->getNext();
        ++index;
    }

    return ptr->getData();
}

std::vector<int> DoubleLinkedList::getValues()
{
    std::vector<int> out;
    DoubleNode* ptr = this->head_;
    while(ptr)
    {
        out.push_back(ptr->getData());
        ptr = ptr->getNext();
    }
    return out;
}

