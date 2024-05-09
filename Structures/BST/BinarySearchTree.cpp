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

BinarySearchTree::BinarySearchTree(BinarySearchTree& obj)
{
    // Make a deep copy of a tree starting from obj.head_
    head_    = deepCopyNode(obj.head_);
    size_    = obj.size_;
    isEmpty_ = obj.isEmpty_;
    std::cout << "Successfully created a BST copied from " << &obj << "\n";
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
        size_ += calculateSize(newNode);
    }
    else
    {
        std::cout << "Could not add value to the BST" << std::endl;
    }


    std::cout << "DBG: size= " << size_ << " isEmpty= " << std::boolalpha << isEmpty_ << std::endl;
}

bool BinarySearchTree::recursiveInserter(TreeNode* node, TreeNode* newNode)
{
    if(!head_)
    {
        head_ = newNode;
        isEmpty_ = false;
        return true;
    }

    if(node)
    {
        int newValue = newNode->data_;
        int currentNodeValue = node->data_;
        if(currentNodeValue == newValue)
        {
            std::cout << newValue << " is already present in the BST\n";
            return false;
        }

        if(currentNodeValue < newValue)
        {
            if(!node->right_)
            {
                node->right_ = newNode;
                return true;
            }

            return recursiveInserter(node->right_, newNode);
        }
        
        if(currentNodeValue > newValue)
        {
            if(!node->left_)
            {
                node->left_ = newNode;
                return true;
            }

            return recursiveInserter(node->left_, newNode);
        }
    }
    
    // Maybe throw error?
    throw std::runtime_error("Impossible Error - Node shall never be nullptr\n");
    return false; //Should never reach here
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

bool BinarySearchTree::recusriveRemover(TreeNode** node, int value)
{
    if((*node)->data_ > value)
    {
        return recusriveRemover(&(*node)->left_, value);
    }
    else if ((*node)->data_ < value)
    {
        return recusriveRemover(&(*node)->right_, value);
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
    
    throw std::runtime_error("Impossible Error - Node shall never be nullptr\n");
    return false; // Should never reach here - just for safety
}

TreeNode* BinarySearchTree::recursiveFinder(TreeNode* node, int targetValue) const
{
    if(node)
    {
        if(targetValue > node->data_)
        {
            return recursiveFinder(node->right_, targetValue);
        }
        else if(targetValue < node->data_)
        {
            return recursiveFinder(node->left_, targetValue);
        }
        else
        {
            std::cout << "Value " << targetValue << " found at " << node << std::endl;
            return node;
        }
    }

    // Value not found
    std::cout << "Could not find value " << targetValue << "\n";
    return nullptr;
}

TreeNode* BinarySearchTree::deepCopyNode(TreeNode* head) const
{
    TreeNode* copiedNode = nullptr;
    if(head)
    {
        copiedNode = new TreeNode(*head);
        if(head->left_)
        {
            copiedNode->left_ = deepCopyNode(head->left_);
        }

        if(head->right_)
        {
            copiedNode->right_ = deepCopyNode(head->right_);
        }
    }

    return copiedNode;
}

BinarySearchTree* BinarySearchTree::getSubTree(int startingHead) const
{
    // 1. Find Node
    TreeNode* findNode = recursiveFinder(head_, startingHead);
    if(!findNode)
    {
        return nullptr;
    }

    TreeNode* newHead;
    // 2. Get the sub tree copy from the tree.
    // Make a deep copy of a given head.
    newHead = deepCopyNode(findNode);

    return new BinarySearchTree(newHead);
}

bool BinarySearchTree::recursiveComperator(TreeNode* lhs, TreeNode* rhs) const
{
    // At this point there are no differences and check is at the end node
    if(!lhs && !rhs)
    {
        return true;
    }

    // One node is not present - differance was found
    if(!lhs || !rhs)
    {
        return false;
    }

    // Data is not the same - differance was found
    if(lhs->data_ != rhs->data_)
    {
        return false;
    }

    // If everything is the same, traverse until end of the tree
    return recursiveComperator(lhs->left_, rhs->left_) &&
           recursiveComperator(lhs->right_, rhs->right_);
}

bool BinarySearchTree::operator == (const BinarySearchTree& comp)
{
    if((size_ != comp.size_) || (isEmpty_ != comp.isEmpty_)) return false;
    return recursiveComperator(head_, comp.head_);
}

void BinarySearchTree::recursiveConverter(TreeNode* node, std::vector<int>& product)
{
    if(node)
    {
        if(node->left_) recursiveConverter(node->left_, product);
        
        product.push_back(node->data_);

        if(node->right_) recursiveConverter(node->right_, product);
    }

    return;
}

std::vector<int>BinarySearchTree::toVector()
{
    std::vector<int> product;
    recursiveConverter(head_, product);
    return product;
}

BinarySearchTree::~BinarySearchTree()
{
    recursiveTeardown(head_);  
}