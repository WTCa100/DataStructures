#ifndef STRUCTURES_COMMON_NODE_SINGLENODE_H
#define STRUCTURES_COMMON_NODE_SINGLENODE_H

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned long size_t;
#endif

// Maybe changed later into class template to make it more unique.

template <typename T>
class SingleNode
{
    private:
        T data_;
        SingleNode* next_;
    public:
        SingleNode() = default;
        SingleNode(T initData) : data_(initData), next_(nullptr) {}

        // Setter
        void setData(T newData) { data_ = newData; }
        void setNext(SingleNode* newNext) { next_ = newNext; }
        // Getter
        T getData() const { return data_; }
        SingleNode* getNext() const { return next_; } 

        ~SingleNode() = default;
};

#endif