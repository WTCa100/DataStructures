#include "Node.hpp"

size_t Node::calculateNodeLenght(const Node* target)
{
    size_t counter = 0;
    Node* helper = const_cast<Node*>(target);
    while(helper)
    {
        ++counter;
        helper = helper->getNext();
    }
    return counter;
}