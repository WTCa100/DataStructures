#ifndef  STRUCTURES_COMMON_NODE_DOUBLENODE_H
#define  STRUCTURES_COMMON_NODE_DOUBLENODE_H

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned long size_t;
#endif

template<typename T>
class DoubleNode
{
    private:
        T data_;
        DoubleNode* next_;
        DoubleNode* prev_;
    public:
        DoubleNode() = delete; // No need for a constructor with garbage
        DoubleNode(T initData) : DoubleNode(initData, nullptr) {}
        DoubleNode(T initData, DoubleNode* prev) : data_(initData), next_(nullptr), prev_(prev) {}
        
        // Methods

        void linkNext(DoubleNode* newNext);
        void linkPrev(DoubleNode* newPrev);

        // Setters
        void setData(const T& newData)   { this->data_ = newData; }
        void setNext(DoubleNode* newNext) { this->next_ = newNext; }
        void setPrev(DoubleNode* newPrev) { this->prev_ = newPrev; }
        // Getters
        T getData() const { return this->data_; }
        DoubleNode* getNext() const { return this->next_; }
        DoubleNode* getPrev() const { return this->prev_; }
        
        ~DoubleNode() = default; 
};

#endif