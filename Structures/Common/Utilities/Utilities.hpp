#ifndef STRUCTURES_COMMON_NODE_UTILITIES_H
#define STRUCTURES_COMMON_NODE_UTILITIES_H

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
} // namespace Utilities


#endif