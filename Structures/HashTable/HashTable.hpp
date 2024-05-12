#ifndef STRUCTURES_HASHSET_HASHTABLE_HPP
#define STRUCTURES_HASHSET_HASHTABLE_HPP

#include <vector>

template <typename K, typename V> 
using bucket = std::vector<std::pair<K, V>>;

template <typename K, typename V>
class HashTable
{
private:
    int hashingRange_;
    size_t size_;
    bool isEmpty_;
    std::vector<bucket> table_;

    int calculateHash(const K& key);
public:
    HashTable() = delete;
    ~HashTable();

    // Insert
    // Delete
    // Contain

    // Getters
    // size
    // hash range
    // is empty
    // bucket? Maybe
    
};


#endif