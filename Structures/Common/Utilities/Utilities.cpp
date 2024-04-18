
#include "./Utilities.hpp"

namespace Utilities
{
    size_t calculateNodeSequenceLenght(const SingleNode* target)
    {
        size_t counter = 0;
        SingleNode* helper = const_cast<SingleNode*>(target);
        while(helper)
        {
            ++counter;
            helper = helper->getNext();
        }
        return counter;
    }
    size_t calculateNodeSequenceLenght(const DoubleNode* target)
    {
        size_t counter = 0;
        DoubleNode* ref = const_cast<DoubleNode*>(target);
        // Handle each next node + target
        DoubleNode* helperFront = ref;
        while(helperFront)
        {
            ++counter;
            helperFront = helperFront->getNext();
        }
        
        // Handle each prev node
        DoubleNode* helperBack = ref->getPrev();
        while(helperBack)
        {
            ++counter;
            helperBack = helperBack->getPrev();
        }
        return counter;
    }
    bool areNodesLinked(const DoubleNode* prev, const DoubleNode* next)
    {
        return prev->getNext() == next &&
               next->getPrev() == prev;
    }
} // namespace Utilities
