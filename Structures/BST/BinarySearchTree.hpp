#include <vector>
#include <cstddef>
#include "../Common/Node/TreeNode.hpp"

#ifndef STRUCTURES_BST_BINARYSEARCHTREE_HPP
#define STRUCTURES_BST_BINARYSEARCHTREE_HPP

template <typename T>
class BinarySearchTree
{
    private:
    TreeNode<T>* head_;
    size_t size_;
    bool isEmpty_;

    // Tools
    size_t calculateSize(TreeNode<T>* node, size_t passedValue = 0);
    void recursiveTeardown(TreeNode<T>* node);
    bool recursiveInserter(TreeNode<T>* node, TreeNode<T>* newNode);
    bool recusriveRemover(TreeNode<T>** node, T value);
    TreeNode<T>* recursiveFinder(TreeNode<T>* node, T targetValue) const;
    bool recursiveComperator(TreeNode<T>* lhs, TreeNode<T>* rhs) const;
    TreeNode<T>* deepCopyNode(TreeNode<T>* head) const;
    void recursiveConverter(TreeNode<T>* node, std::vector<T>& product);

    public:
    BinarySearchTree() : BinarySearchTree<T>(nullptr) {}
    BinarySearchTree(T headValue) : BinarySearchTree<T>(new TreeNode<T>(headValue)) {}
    BinarySearchTree(TreeNode<T>* head);
    BinarySearchTree(BinarySearchTree<T>& obj);
    ~BinarySearchTree();

    void insert(T value);
    void insert(TreeNode<T>* newNode);
    void remove(T value);
    BinarySearchTree<T>* getSubTree(T startingHead) const;
    bool isPresent(T value) const { return recursiveFinder(head_, value); } // I guess this is not needed
    inline TreeNode<T>* getNodeFromValue(T value) const { return recursiveFinder(head_, value); }
    std::vector<T> toVector(); // Will always be sorted

    TreeNode<T>* getHead() const { return head_; }
    size_t getSize() const { return size_; }
    bool isEmpty() const { return isEmpty_; }
    bool operator == (const BinarySearchTree<T>& comp);
    inline bool operator != (const BinarySearchTree<T>& comp) { return !(*this == comp); }
};

#endif

