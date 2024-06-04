#ifndef STRUCTURES_COMMON_NODE_TREENODE_HPP
#define STRUCTURES_COMMON_NODE_TREENODE_HPP

// This can be alternatively swapped to a friend class of BinarySeachTree
template <typename T>
struct TreeNode
{
    T data_;
    TreeNode<T>* left_;
    TreeNode<T>* right_;

    // Ctors : Dtors
    TreeNode() = default;
    TreeNode(T data) : data_(data), left_(nullptr), right_(nullptr) {}
    TreeNode(const TreeNode& obj);
    ~TreeNode() = default;
};

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
#endif
