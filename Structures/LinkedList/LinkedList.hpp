#ifndef STRUCTURES_LINKEDLIST_LINKEDLIST_HPP
#define STRUCTURES_LINKEDLIST_LINKEDLIST_HPP

// Interface file
#include <vector>

template <typename T>
class LinkedList
{
    protected:
    size_t size_;
    bool isEmpty_;
    public:
    LinkedList() = delete;
    LinkedList(size_t size, bool isEmpty) : size_(size), isEmpty_(isEmpty) {}
    virtual ~LinkedList() {}
    
    // Removing
    virtual void popHead() = 0;
    virtual void popBack() = 0;
    virtual void popAt(const size_t& pos) = 0; 
    // Adding
    virtual void insertHead(const T& newValue) = 0;
    virtual void pushBack(const T& newValue) = 0;
    virtual void insertAt(const T& newValue, const size_t& pos) = 0;
    // Parsing
    virtual bool isPresent(const T& value) const = 0;
    virtual void parse() const = 0;

    // Getters
    bool isEmpty() { return isEmpty_; }
    size_t getSize() { return size_; }
    virtual T at(const size_t& pos) = 0;
    virtual std::vector<T> getValues() = 0;
};

#endif //STRUCTURES_LINKEDLIST_LINKEDLIST_HPP