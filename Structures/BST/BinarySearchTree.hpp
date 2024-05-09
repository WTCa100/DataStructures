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
    bool recursiveInserter(TreeNode* node, TreeNode* newNode);
    bool recusriveRemover(TreeNode** node, int value);
    TreeNode* recursiveFinder(TreeNode* node, int targetValue) const;
    bool recursiveComperator(TreeNode* lhs, TreeNode* rhs) const;
    TreeNode* deepCopyNode(TreeNode* head) const;
    void recursiveConverter(TreeNode* node, std::vector<int>& product);

    public:
    BinarySearchTree() : BinarySearchTree(nullptr) {}
    BinarySearchTree(int headValue) : BinarySearchTree(new TreeNode(headValue)) {}
    BinarySearchTree(TreeNode* head);
    BinarySearchTree(BinarySearchTree& obj);
    ~BinarySearchTree();

    void insert(int value);
    void insert(TreeNode* newNode);
    void remove(int value);
    BinarySearchTree* getSubTree(int startingHead) const;
    bool isPresent(int value) const { return recursiveFinder(head_, value); } // I guess this is not needed
    inline TreeNode* getNodeFromValue(int value) const { return recursiveFinder(head_, value); }
    std::vector<int> toVector(); // Will always be sorted

    TreeNode* getHead() const { return head_; }
    size_t getSize() const { return size_; }
    bool isEmpty() const { return isEmpty_; }
    bool operator == (const BinarySearchTree& comp);
    inline bool operator != (const BinarySearchTree& comp) { return !(*this == comp); }
};

#endif

