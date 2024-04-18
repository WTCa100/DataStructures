#ifndef STRUCTURES_COMMON_NODE_UTILITIES_H
#define STRUCTURES_COMMON_NODE_UTILITIES_H

#include "../Node/DoubleNode.hpp"
#include "../Node/SingleNode.hpp"

namespace Utilities
{
    size_t calculateNodeSequenceLenght(const SingleNode* target);
    size_t calculateNodeSequenceLenght(const DoubleNode* target);
    bool areNodesLinked(const DoubleNode* prev, const DoubleNode* next);
} // namespace Utilities


#endif