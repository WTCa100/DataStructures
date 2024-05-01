#include <vector>
#include <cstddef>
#include "../Common/Node/TreeNode.hpp"

#ifndef STRUCTURES_BST_BINARYSEARCHTREE_HPP
#define STRUCTURES_BST_BINARYSEARCHTREE_HPP


class BinarySearchTree
{
    private:
    TreeNode* head_;
    size_t size_;
    bool isEmpty_;

    // Tools
    size_t calculateSize(TreeNode* node, size_t passedValue = 0);
    void recursiveTeardown(TreeNode* node);
    bool recursiveInserter(TreeNode* node, TreeNode* newNode, bool result = false);
    bool recusriveRemover(TreeNode** node, /*TreeNode* parent,*/ int value, bool result = false);
    TreeNode* recursiveFinder(TreeNode* node, int targetValue, TreeNode* returnNode);

    public:
    BinarySearchTree() : BinarySearchTree(nullptr) {}
    BinarySearchTree(int headValue) : BinarySearchTree(new TreeNode(headValue)) {}
    BinarySearchTree(TreeNode* head);
    ~BinarySearchTree();

    void insert(int value);
    void insert(TreeNode* newNode);
    void remove(int value);
    BinarySearchTree* getSubTree(int startingHead) const;
    BinarySearchTree* getSubTree(TreeNode* startingHead) const;
    bool isPresent(int value) const;
    std::vector<int> toVector(); // Will always be sorted

    int getHead() const { return head_->data_; }
    size_t getSize() const { return size_; }
    bool isEmpty() const { return isEmpty_; }
};

#endif

