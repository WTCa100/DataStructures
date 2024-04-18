#include "./DoubleNode.hpp"

/// @brief Will set new next to this node and set this node as prev for the new node.
/// Will only set next if newNext is not NULL.
/// @param newNext 
void DoubleNode::linkNext(DoubleNode* newNext)
{
    this->setNext(newNext);
    if(newNext)
    {
        newNext->setPrev(this);
    }
}

/// @brief Will set new prev to this node and set this node as next for the new node.
/// Will only set next if newNext is not NULL.
/// @param newPrev 
void DoubleNode::linkPrev(DoubleNode* newPrev)
{
    this->setNext(newPrev);
    if(newPrev)
    {
        newPrev->setPrev(this);
    }
}