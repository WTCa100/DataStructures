// Interface file
#include <vector>

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
    virtual void insertHead(const int& newValue) = 0;
    virtual void pushBack(const int& newValue) = 0;
    virtual void insertAt(const int& newValue, const size_t& pos) = 0;
    // Parsing
    virtual bool isPresent(const int& value) const = 0;
    virtual void parse() const = 0;

    // Getters
    bool isEmpty() { return this->isEmpty_; }
    size_t getSize() { return this->size_; }
    virtual int at(const size_t& pos) = 0;
    virtual std::vector<int> getValues() = 0;
};