#include "./TreeNode.hpp"

/// @brief Will return a copy of a given node with the same data_ value attribute
/// @note This constructor will not assign left_ and right_ pointer values
/// @param obj 
template <typename T>
TreeNode<T>::TreeNode(const TreeNode<T>& obj)
{
    data_  = obj.data_;
    // The copy shall not point to the same data as the original object
    left_  = nullptr;
    right_ = nullptr;
}