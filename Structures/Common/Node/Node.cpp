#include "Node.hpp"

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
        DoubleLinked::Node* helper = const_cast<DoubleLinked::Node*>(target);
        while(helper)
        {
            ++counter;
            helper = helper->getNext();
        }
        return counter;
    }
} // namespace Utils