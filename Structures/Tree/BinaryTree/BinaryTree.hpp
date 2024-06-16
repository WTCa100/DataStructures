#ifndef STRUCTURES_TREE_BINARYTREE_HPP
#define STRUCTURES_TREE_BINARYTREE_HPP

#include "../../Common/Node/TreeNode.hpp"

#include <queue>

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned long size_t;
#endif

template<typename T>
class BinaryTree
{
public:
    enum converterOrder
    {
        inorder = 0,
        preorder,
        postorder
    };

private:
    TreeNode<T>* root_;
    size_t      size_;
    bool        isEmpty_;

    // Tools
    // TreeNode<T>* DBG_getRoot() { return root_; } 
    size_t calculateSize(TreeNode<T>* node, size_t passedValue = 0);
    void recursiveTeardown(TreeNode<T>* node);
    bool recursiveInserter(TreeNode<T>* node, TreeNode<T>* newNode);
    bool recusriveRemover(TreeNode<T>** node, T value);
    TreeNode<T>* recursiveFinder(TreeNode<T>* node, T targetValue) const;
    void recursiveConverter(TreeNode<T>* node, std::vector<T>& product, const converterOrder& order) const;

public:
    BinaryTree() : BinaryTree<T>(nullptr) {}
    BinaryTree(T initVal) : BinaryTree<T>(new TreeNode<T>(initVal)){}
    BinaryTree(TreeNode<T>* root);
    ~BinaryTree();

    void insert(T value);
    void insert(TreeNode<T>* newNode);
    TreeNode<T>* getNodeFromValue(T value) const;
    inline bool isPresent(T value) const { return recursiveFinder(root_, value); }
    std::vector<T> toVector(const converterOrder& order) const;
    void remove(T value);
};

template <typename T>
size_t BinaryTree<T>::calculateSize(TreeNode<T>* node, size_t passedValue)
{   
    if(node)
    {
        // For remaining head
        ++passedValue;
        passedValue += calculateSize(node->left_);
        passedValue += calculateSize(node->right_);
    }
    return passedValue;
}

template <typename T>
BinaryTree<T>::BinaryTree(TreeNode<T>* root)
{
    root_ = root;
    if(!root_)
    {
        std::cout << "WARN!!! Passed TreeNode is a nullptr." << std::endl;
        size_ = 0;
        isEmpty_ = true;
    }
    else
    {
        size_ =calculateSize(root_);
        isEmpty_ = false; 
    }

    root_ ? std::cout << "Successfully created a Binary Tree with head at " << root_ << " value= " << root_->data_ << " size= " << size_ << std::endl 
          : std::cout << "Successfully created a Binary Tree with head at " << root_ << " size= " << size_ << std::endl;
}

template <typename T>
bool BinaryTree<T>::recursiveInserter(TreeNode<T>* node, TreeNode<T>* newNode)
{

    std::queue<TreeNode<T>*> nodeLevel;
    nodeLevel.push(node);

    while(nodeLevel.size())
    {
        TreeNode<T>* helper = nodeLevel.front();
        std::cout << "Current root " << helper->data_ << "\n";
        // Remove the element from the current level 
        nodeLevel.pop();
        
        // Check if there is a missing left child
        if(!helper->left_)
        {
            std::cout << "Added as a left child" << std::endl;
            helper->left_ = newNode;
            return true;
        }
        // Left child exists - adding to the new queue level
        nodeLevel.push(helper->left_);

        // Check if there is a missing right child
        if(!helper->right_)
        {
            std::cout << "Added as a right child" << std::endl;
            helper->right_ = newNode;
            return true;
        }

        // right child exists - adding to the nw queu level
        nodeLevel.push(helper->right_);

    }

    // A rather impossible place to be
    throw std::runtime_error("Impossible Error - Node shall never be nullptr\n");
    return false;
}


template <typename T>
void BinaryTree<T>::insert(T value)
{
    insert(new TreeNode<T>(value));
}

template <typename T>
void BinaryTree<T>::insert(TreeNode<T>* newNode)
{
    if(!newNode)
    {
        std::cout << "Cannot insert given node into the Binary Tree - node is empty." << std::endl;
        return;
    }

    if(isPresent(newNode->data_))
    {
        std::cout << "Cannot insert given node into the Binary Tree - value is a duplicate." << std::endl;
        return;
    }

    if(recursiveInserter(root_, newNode))
    {
        std::cout << "Successfully added new node (value= " << newNode->data_ << ") to the Binary Tree" << std::endl;
        size_ += calculateSize(newNode);
    }
    else
    {
        std::cout << "Could not add value to the Binary Tree" << std::endl;
    }

    if(size_) isEmpty_ = false;
    std::cout << "DBG: size= " << size_ << " isEmpty= " << std::boolalpha << isEmpty_ << std::endl;

}

template <typename T>
std::vector<T> BinaryTree<T>::toVector(const converterOrder& order) const
{
    std::vector<T> product;
    recursiveConverter(root_, product, order);
    return product;
}

template <typename T>
void BinaryTree<T>::recursiveConverter(TreeNode<T>* node, std::vector<T>& product, const converterOrder& order) const
{
    if(node)
    {
        switch (order)
        {
        case converterOrder::inorder:
            recursiveConverter(node->left_, product, order);
            product.push_back(node->data_);
            recursiveConverter(node->right_, product, order);
            break;
        case converterOrder::preorder:
            product.push_back(node->data_);
            recursiveConverter(node->left_, product, order);
            recursiveConverter(node->right_, product, order);
            break;
        case converterOrder::postorder:
            recursiveConverter(node->left_, product, order);
            recursiveConverter(node->right_, product, order);
            product.push_back(node->data_);
            break;
        }
    }
}

template <typename T>
void BinaryTree<T>::remove(T value)
{
    std::cout << "Trying to remove " << value << " from the Binary Tree " << "\n";
    if(isEmpty_) 
    {
        std::cout << "BST is empty.\n" << std::endl;
        return;
    }
    
    if(recusriveRemover(&root_, value))
    {
        std::cout << "Successfully deleted " << value << " from the Binary Tree" << std::endl;
        --size_;
        if(!size_) isEmpty_ = true;
    }
    else
    {
        std::cout << "Could not find " << value << " in the Binary Tree" << std::endl;
    }
    
    std::cout << "DBG: size= " << size_ << " isEmpty= " << std::boolalpha << isEmpty_ << std::endl;
}

template <typename T>
TreeNode<T>* BinaryTree<T>::getNodeFromValue(T value) const
{
    if(isEmpty_ || !size_)
    {
        std::cout << "Binary tree is empty, no values are present!" << std::endl;
        return nullptr;
    }

    return recursiveFinder(root_, value);
}

template <typename T>
TreeNode<T>*  BinaryTree<T>::recursiveFinder(TreeNode<T>* node, T targetValue) const
{
    if(!node)
    {
        return nullptr;
    }

    if(node->data_ == targetValue)
    {
        return node;
    }

    // Handle left first
    TreeNode<T>* helper = recursiveFinder(node->left_, targetValue);
    if(!helper)
    {
        helper = recursiveFinder(node->right_, targetValue);
    }

    return helper;
}

template <typename T>
bool BinaryTree<T>::recusriveRemover(TreeNode<T>** node, T value)
{
    if(*node)
    {
        if((*node)->data_ == value)
        {
            std::cout << "Found value " << value << " at " << *node << "\n";
            // Case 1: No siblings - delete
            if(!(*node)->left_ && !(*node)->right_)
            {
                std::cout << "Single node - normal delete" << std::endl;
                delete (*node);
                (*node) = nullptr;
                return true;
            }
            
            // Case 2: Has at least one sibling
            // In order to delete a node in this scenario, we need to get the deepest node from the right side of the tree (right-most end-node)
            std::cout << "Node with children - getting the right most deepest node\n";
            TreeNode<T>* endNodeParent = *node;
            TreeNode<T>* endNode = (*node)->right_;

            while (endNode->right_)
            {
                endNodeParent = endNode;
                endNode = endNode->right_;
            }
            std::cout << "Replacer = " << endNode << " val= " << endNode->data_ << "\n";

            // We then swap the nodes
            (*node)->data_ = endNode->data_;
            delete(endNode);
            endNodeParent->right_ = nullptr;

            std::cout << "DBG: New value at target node " << (*node)->data_ << "\n";
            std::cout << "Successfully deleted desired node" << std::endl;
            return true;
        }

        // Node does not have a desired value - check left and right node
        return (recusriveRemover(&(*node)->left_, value) || recusriveRemover(&(*node)->right_, value));

    }
    
    // After the end node
    return false;    
    // throw std::runtime_error("Impossible Error - Node shall never be nullptr\n");
    // return false; // Should never reach here - just for safety
}

template <typename T>
void BinaryTree<T>::recursiveTeardown(TreeNode<T>* node)
{
    if(node)
    {
        recursiveTeardown(node->left_);
        recursiveTeardown(node->right_);
        node->left_  = nullptr;
        node->right_ = nullptr;
        delete(node);
        node = nullptr;
    }
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    recursiveTeardown(root_);
}

#endif