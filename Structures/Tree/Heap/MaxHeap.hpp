#ifndef STRUCTURES_TREE_MAXHEAP_HPP
#define STRUCTURES_TREE_MAXHEAP_HPP

#include <iostream>
#include <vector>
#include <cstddef>
#include "../BinaryTree/BinaryTree.hpp"

template <typename T>
class MaxHeap
{
private:
    std::vector<T> data_;

    void maintainUp(size_t index);
    void maintainDown(size_t index);
public:
    MaxHeap() = default;
    ~MaxHeap() = default;

    inline size_t getLChildIndex(size_t index) { return 2 * index + 1; }
    inline size_t getRChildIndex(size_t index) { return 2 * index + 2; }
    size_t getParentIndex(size_t index) { return (index - 1) / 2; }
    inline size_t getSize() const { return data_.size(); }
    inline bool isEmpty() const { return data_.empty(); }


    void insert(T value);
    void removeTop();
    T* extract();
    T at(size_t index);
    T getMax();
    bool exists(size_t index);
    bool exists(T value);
    // size_t* find(T value);
    void Heapify(BinaryTree<T>* target);
};

template <typename T>
bool MaxHeap<T>::exists(T value)
{
    return (std::find(data_.begin(), data_.end(), value) != data_.end());
}

template <typename T>
void MaxHeap<T>::insert(T value)
{
    std::cout << "Inserting value into the heap\n";

    data_.push_back(value);
    maintainUp(data_.size() - 1);

    std::cout << "Value inserted!\n";
    #ifdef DBG_MODE
    std::cout << "DBG: data_->size() = " << data_.size() << std::endl;
    #endif
} 

template <typename T>
T MaxHeap<T>::getMax()
{
    if(!data_.size())
    {
        throw std::runtime_error("Index of 0 is out of bound");
    }

    return data_.at(0);
}

template <typename T>
void MaxHeap<T>::removeTop()
{
    if(isEmpty())
    {
        std::cout << "No top to remove" << std::endl;
        return;
    }

    std::cout << "Deleting the " << data_.at(0) << "\n";
    data_.erase(data_.begin());
    std::cout << "New head = " << data_.at(0) << "\n";

    maintainDown(0);
    std::cout << "After Maintnance: New head = " << data_.at(0) << "\n";
}

template <typename T>
T* MaxHeap<T>::extract()
{
    if(isEmpty())
    {
        std::cout << "Cannot extract from the heap - heap is empty" << std::endl;
        return nullptr;
    }

    std::cout << "Extracting the first value from the data_\n";
    T product = data_.at(0);
    data_.erase(data_.begin());

    maintainDown(0);

    #ifdef DBG_MODE
    std::cout << "DBG: data_->size() " <<  data_.size() << std::endl;
    #endif
    return std::move(&product);

}

template <typename T>
void MaxHeap<T>::maintainUp(size_t index)
{
    // Start from the given index and move up - checking if a value at given index is greater than it's parent
    while(index > 0)
    {
        size_t parentIndex = getParentIndex(index);
        if(data_.at(index) > data_.at(parentIndex))
        {
            std::swap(data_.at(index), data_.at(parentIndex));
        }

        index = parentIndex;
    } 
}

template <typename T>
void MaxHeap<T>::maintainDown(size_t index)
{
    size_t greatest   = index;
    size_t leftChild  = getLChildIndex(index);
    size_t rightChild = getRChildIndex(index);

    if(leftChild >= data_.size() && rightChild >= data_.size())
    {
        return;
    }

    // Check if child exists
    if(leftChild < data_.size())
    { 
        // Check if it's greater than current largest
        if(data_.at(leftChild) > data_.at(greatest))
        {
            greatest = leftChild;
        }
    }

    // Do the same for a right child
    if(rightChild < data_.size())
    {
        if(data_.at(rightChild) > data_.at(greatest))
        {
            greatest = rightChild;
        }
    }

    // Now if the greatest node is not the current index, swap the data
    if(greatest != index)
    {
        std::swap(data_.at(index), data_.at(greatest));
    }

    // Ensure that the lower levels follow the same rule
    maintainDown(getLChildIndex(index));
    maintainDown(getRChildIndex(index));
}


/// @brief This function will return value from the heap in a given index position.
/// @param index Where?
/// @return Value of data at given index.
/// @warning This may lead to crash so make sure you know what you are doing while using it.
template <typename T>
T MaxHeap<T>::at(size_t index)
{
    return data_.at(index);
}

template <typename T>
bool MaxHeap<T>::exists(size_t index)
{
    return data_.size() < index;
}


#endif