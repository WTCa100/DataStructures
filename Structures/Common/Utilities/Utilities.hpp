#ifndef STRUCTURES_COMMON_UTILITIES_H
#define STRUCTURES_COMMON_UTILITIES_H

#include "../Node/DoubleNode.hpp"
#include "../Node/SingleNode.hpp"

namespace Utilities
{
    template <typename T>
    size_t calculateNodeSequenceLenght(const SingleNode<T>* target);
    template <typename T>
    size_t calculateNodeSequenceLenght(const DoubleNode<T>* target);
    template <typename T>
    bool areNodesLinked(const DoubleNode<T>* prev, const DoubleNode<T>* next);

    template <typename T>
    size_t calculateNodeSequenceLenght(const SingleNode<T>* target)
    {
        size_t counter = 0;
        SingleNode<T>* helper = const_cast<SingleNode<T>*>(target);
        while(helper)
        {
            ++counter;
            helper = helper->getNext();
        }
        return counter;
    }

    template <typename T>
    size_t calculateNodeSequenceLenght(const DoubleNode<T>* target)
    {
        size_t counter = 0;
        DoubleNode<T>* ref = const_cast<DoubleNode<T>*>(target);
        // Handle each next node + target
        DoubleNode<T>* helperFront = ref;
        while(helperFront)
        {
            ++counter;
            helperFront = helperFront->getNext();
        }
        
        // Handle each prev node
        DoubleNode<T>* helperBack = ref->getPrev();
        while(helperBack)
        {
            ++counter;
            helperBack = helperBack->getPrev();
        }
        return counter;
    }

    template <typename T>
    bool areNodesLinked(const DoubleNode<T>* prev, const DoubleNode<T>* next)
    {
        return prev->getNext() == next &&
               next->getPrev() == prev;
    }

} // namespace Utilities
#endif
