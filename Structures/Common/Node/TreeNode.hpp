#ifndef STRUCTURES_COMMON_NODE_TREENODE_HPP
#define STRUCTURES_COMMON_NODE_TREENODE_HPP

// This can be alternatively swapped to a friend class of BinarySeachTree
struct TreeNode
{
    int data_;
    TreeNode* left_;
    TreeNode* right_;

    // Ctors : Dtors
    TreeNode() = default;
    TreeNode(int data) : data_(data), left_(nullptr), right_(nullptr) {}
    TreeNode(const TreeNode& obj);
    ~TreeNode() = default;
};

#endif
