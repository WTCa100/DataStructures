#include "./DoubleNode.hpp"

/// @brief Will set new next to this node and set this node as prev for the new node.
/// Will only set next if newNext is not NULL.
/// @param newNext 
template <typename T>
void DoubleNode<T>::linkNext(DoubleNode<T>* newNext)
{
    setNext(newNext);
    if(newNext)
    {
        newNext->setPrev(this);
    }
}

/// @brief Will set new prev to this node and set this node as next for the new node.
/// Will only set next if newNext is not NULL.
/// @param newPrev
template <typename T> 
void DoubleNode<T>::linkPrev(DoubleNode<T>* newPrev)
{
    setNext(newPrev);
    if(newPrev)
    {
        newPrev->setPrev(this);
    }
}