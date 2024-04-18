#ifndef STRUCTURES_COMMON_NODE_SINGLENODE_H
#define STRUCTURES_COMMON_NODE_SINGLENODE_H

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned long size_t;
#endif

// Maybe changed later into class template to make it more unique.

class SingleNode
{
    private:
        int data_;
        SingleNode* next_;
    public:
        SingleNode() : SingleNode(0) {};
        SingleNode(int initData) : data_(initData), next_(nullptr) {}

        // Setter
        void setData(int newData) { this->data_ = newData; }
        void setNext(SingleNode* newNext) { this->next_ = newNext; }
        // Getter
        int getData() const { return this->data_; }
        SingleNode* getNext() const { return this->next_; } 

        ~SingleNode() = default;
};

#endif