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

#endif
