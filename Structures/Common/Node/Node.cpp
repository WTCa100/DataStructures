#include "Node.hpp"

namespace DoubleLinked
{
    /// @brief Will set new next to this node and set this node as prev for the new node.
    /// Will only set next if newNext is NULL.
    /// @param newNext 
    void Node::setNext(Node* newNext)
    {
        if(!newNext)
        {
            this->next_ = newNext;
            return;
        }
        this->next_ = newNext;
        newNext->prev_ = this;
        return;
    }
    /// @brief Will set new prev to this node and set this node as next for the new node.
    /// Will only set next if newNext is NULL.
    /// @param newPrev 
    void Node::setPrev(Node* newPrev)
    {
        if(!this->prev_)
        {
            this->prev_ = newPrev;
            return;
        }
        this->prev_ = newPrev;
        newPrev->next_ = this;
    }
} // namespace DoubleLinked

namespace Utils
{

    size_t calculateNodeLenght(const SingleLinked::Node* target)
    {
        size_t counter = 0;
        SingleLinked::Node* helper = const_cast<SingleLinked::Node*>(target);
        while(helper)
        {
            ++counter;
            helper = helper->getNext();
        }
        return counter;
    }
    size_t calculateNodeLenght(const DoubleLinked::Node* target)
    {
        size_t counter = 0;
        DoubleLinked::Node* ref = const_cast<DoubleLinked::Node*>(target);
        // Handle each next node + target
        DoubleLinked::Node* helperFront = ref;
        while(helperFront)
        {
            ++counter;
            helperFront = helperFront->getNext();
        }
        
        // Handle each prev node
        DoubleLinked::Node* helperBack = ref->getPrev();
        while(helperBack)
        {
            ++counter;
            helperBack = helperBack->getPrev();
        }
        return counter;
    }
} // namespace Utils