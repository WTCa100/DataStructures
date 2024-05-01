#include <iostream>
#include "BinarySearchTree.hpp"


size_t BinarySearchTree::calculateSize(TreeNode* node, size_t passedValue)
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

void BinarySearchTree::recursiveTeardown(TreeNode* node)
{
    if(node)
    {
        recursiveTeardown(node->left_);
        recursiveTeardown(node->right_);
        node->left_ = nullptr;
        node->right_ = nullptr;
        delete(node);
        node = nullptr;
    }
}

BinarySearchTree::BinarySearchTree(TreeNode* head)
{
    head_ = head;
    if(!head_)
    {
        std::cout << "WARN!!! Passed TreeNode is a nullptr." << std::endl;
        size_ = 0;
        isEmpty_ = true;
    }
    else
    {
        size_ =calculateSize(head_);
        isEmpty_ = false; 
    }

    head_ ? std::cout << "Successfully created a BST with head at " << head_ << " value= " << head_->data_ << " size= " << size_ << std::endl 
          : std::cout << "Successfully created a BST with head at " << head_ << " size= " << size_ << std::endl;
}

void BinarySearchTree::insert(int value)
{
    insert(new TreeNode(value));
}

void BinarySearchTree::insert(TreeNode* newNode)
{
    if(!newNode)
    {
        std::cout << "Cannot insert given node into the BST - node is null" << std::endl;
        return; 
    }

    if(recursiveInserter(head_, newNode))
    {
        std::cout << "Successfully added new node (value= " << newNode->data_ << ") to the BST" << std::endl;
        ++size_;
    }
    else
    {
        std::cout << "Could not add value to the BST" << std::endl;
    }


    std::cout << "DBG: size= " << size_ << " isEmpty= " << std::boolalpha << isEmpty_ << std::endl;
}

bool BinarySearchTree::recursiveInserter(TreeNode* node, TreeNode* newNode, bool result)
{
    int newValue = newNode->data_;
    if(!head_)
    {
        head_ = newNode;
        result = true;
        isEmpty_ = false;
    }
    else if(node)
    {
        int currentNodeValue = node->data_;
        if(currentNodeValue == newValue)
        {
            std::cout << newValue << " is already present in the BST\n";
            return false;
        }

        if(currentNodeValue > newValue)
        {
            if(node->right_)
            {
                result = recursiveInserter(node->right_, newNode);
            }
            else
            {
                node->right_ = newNode;
                return true;
            }
        }
        
        if(currentNodeValue < newValue)
        {
            if(node->left_)
            {
                result = recursiveInserter(node->left_, newNode);
            }
            else
            {
                node->left_ = newNode;
                return true;
            }
        }
    }
    return result;
}

void BinarySearchTree::remove(int value)
{
    std::cout << "Trying to remove " << value << " from BST " << "\n";
    if(isEmpty_) 
    {
        std::cout << "BST is empty.\n" << std::endl;
        return;
    }
    
    if(recusriveRemover(&head_, value))
    {
        std::cout << "Successfully deleted " << value << " from BST" << std::endl;
        --size_;
        if(!size_) isEmpty_ = true;
    }
    else
    {
        std::cout << "Could not find " << value << " in linked list" << std::endl;
    }
    
    std::cout << "DBG: size= " << size_ << " isEmpty= " << std::boolalpha << isEmpty_ << std::endl;
}

bool BinarySearchTree::recusriveRemover(TreeNode** node, /*TreeNode* parent,*/ int value, bool result)
{
    if((*node)->data_ > value)
    {
        result = recusriveRemover(&(*node)->left_, value);
    }
    else if ((*node)->data_ < value)
    {
        result = recusriveRemover(&(*node)->right_, value);
    }
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
        
        // Case 2: At least one sibling
        if(!(*node)->left_)
        {
            std::cout << "Single sibling on right side - swapping values\n";
            TreeNode* tmp = (*node)->right_;
            delete(*node);
            *node = tmp;
            std::cout << "Value sawpped to " << tmp->data_ << " from " << tmp << std::endl;
            return true;
        }
        if(!(*node)->right_)
        {
            std::cout << "Single sibling on left side - swapping values\n";
            TreeNode* tmp = (*node)->left_;
            delete(*node);
            *node = tmp;
            std::cout << "Value sawpped to " << tmp->data_ << std::endl;
            return true;
        }
        
        // Case 3: Both siblings are present
        std::cout << "Both sibling present - finding the next in order successor\n";
        TreeNode* successorParent = *node;
        TreeNode* successor = (*node)->right_;
        while(successor->left_)
        {
            successorParent = successor;
            successor = successor->left_;
        }

        successorParent->left_  == successor ?
        successorParent->left_  = successor->right_ :
        successorParent->right_ = successor->right_;

        // Replace values
        std::cout << "Successor found at " << successor << " value= " << successor->data_ << "\n";
        (*node)->data_ = successor->data_;
        
        std::cout << "Value sawpped to new successor " << successor->data_ << " from " << successor << std::endl;
        delete successor;
        return true;
    }

    return result;
}

BinarySearchTree::~BinarySearchTree()
{
    recursiveTeardown(head_);  
}