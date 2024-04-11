#ifndef STRUCTURES_COMMON_NODE_H
#define STRUCTURES_COMMON_NODE_H

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned long size_t;
#endif

// Maybe changed later into class template to make it more unique.

namespace SingleLinked
{
    class Node
    {
        private:
            int data_;
            Node* next_;
        public:
            Node() : Node(0) {};
            Node(int initData) : data_(initData), next_(nullptr) {}

            // Setter
            void setData(int newData) { this->data_ = newData; }
            void setNext(Node* newNext) { this->next_ = newNext; }
            // Getter
            int getData() const { return this->data_; }
            Node* getNext() const { return this->next_; } 

            ~Node() = default;
    };
} // namespace SingleLinked

namespace DoubleLinked
{
    class Node
    {
        private:
            int data_;
            Node* next_;
            Node* prev_;
        public:
            Node() : Node(0) {}
            Node(int initData) : Node(initData, nullptr) {}
            Node(int initData, Node* prev) : data_(initData), next_(nullptr), prev_(prev) {}
            
            // Setters
            void setData(int newData)   { this->data_ = newData; }
            void setNext(Node* newNext) { this->next_ = newNext; }
            void setPrev(Node* newPrev) { this->prev_ = newPrev; }
            // Getters
            int getData() const { return this->data_; }
            Node* getNext() const { return this->next_; }
            Node* getPrev() const { return this->prev_; }
            
            ~Node() = default; 
    };
} // namespace DoubleLinked


namespace Utils
{
    size_t calculateNodeLenght(const SingleLinked::Node* target);
    size_t calculateNodeLenght(const DoubleLinked::Node* target);
} // namespace Utils


#endif