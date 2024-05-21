#ifndef STRUCTURES_HASHSET_HASHTABLE_HPP
#define STRUCTURES_HASHSET_HASHTABLE_HPP

#include <vector>
#include <cstdint>
#include <functional>
#include <iostream>


#define DBG_MODE

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned long size_t;
#endif

template <typename K, typename V> 
using bucket = std::vector<std::pair<K, V>>;

template <typename K, typename V>
class HashTable
{
private:

    enum class resizeVariant
    {
        grow   = 0,
        shrink = 1
    };

    size_t hashingRange_;
    size_t size_;
    bool isEmpty_;
    std::vector<bucket<K, V>> table_;
    bool allowDynamicHashing_;

    size_t calculateHash(const K& key, const size_t& range);
    float loadFactor();
    bool resize(resizeVariant variant);
public:
    HashTable() = delete;
    HashTable(size_t hashRange);
    ~HashTable();

    void insert(const K& key, const V& value);
    void remove(const K& key);
    bool contain(const K& key); 
    void showStatus(std::ostream& os) const;

    // Getters
    size_t getSize() const { return size_;}
    size_t getHashingRange() const { return hashingRange_; }
    bool isEmpty() const { return isEmpty_; }
    bool isDynamicHashing() const { return allowDynamicHashing_; }

    // Setters
    void setDynamicHashing(const bool& flag) { allowDynamicHashing_ = flag; }

    // Debug (for now)
    inline bool DBG_resize() { return resize(resizeVariant::grow); }

    // We generally don't want to give the user power to alter the contents of given buckets and it's values
    // It will be switched later on so that the getBucket/-Entry will return pointer from private function
    bucket<K, V>* getBucket(const K& key);
    std::pair<K, V>* getBucketEntry(const K& key);
};

// In order for the compiler and linker to correctly handle this type of files we need to include class function definitions
// in the same translation unit so that the linker can correctly handle definition linkage.

template <typename K, typename V>
HashTable<K, V>::HashTable(size_t hashRange)
{
    table_.reserve(hashRange);
    hashingRange_ = hashRange;
    
    // Initialize table with empty buckets
    for(size_t i = 0; i < hashingRange_; i++)
    {
        bucket<K, V> currentBucket;
        table_.push_back(currentBucket);
    }
    size_         = 0;
    isEmpty_      = true;
}

template <typename K, typename V>
size_t HashTable<K, V>::calculateHash(const K& key, const size_t& range)
{
    // return std::hash<K>{}(key) % hashingRange_;
    size_t returnVal = std::hash<K>{}(key) % range;
    // std::cout << "Got hash " << returnVal << " from KEY\n";
    return returnVal; 
}


template <typename K, typename V>
float HashTable<K, V>::loadFactor()
{
    return static_cast<double>(size_) / static_cast<double>(hashingRange_);
}

template <typename K, typename V>
bool HashTable<K, V>::resize(resizeVariant variant)
{
    if(size_ == 0 || size_ == 1)
    {
        throw std::runtime_error("This resize should not happen - size = 0 or 1");
    }

    // Create a new vectotor with either size * 2 or size / 2
    size_t newRange = 0;
    variant == resizeVariant::grow ? newRange = hashingRange_ * 2 : newRange = hashingRange_ / 2;

    std::vector<bucket<K, V>> newTable(newRange);
    for(auto& entry : newTable)
    {
        bucket<K, V> currentBucket;
        entry = currentBucket;
    }

    // Assign all values to the new table
    for(auto& entry : table_)
    {
        for(auto& pair : entry)
        {
            newTable[calculateHash(pair.first, newRange)].push_back(std::move(pair));
        }
    }

    table_ = newTable;
    hashingRange_ = newRange;
    std::cout << "DBG: New table with size: " << hashingRange_ << std::endl;
    return true;
}


template <typename K, typename V>
void HashTable<K, V>::insert(const K& key, const V& value)
{
    auto targetBucket = getBucket(key);
    
    // Make a pair from entry
    std::pair<K, V> entry = std::make_pair(key, value);
   
    // Check if a given entry (key) already exists on a given bucket
    auto present = std::find_if(targetBucket->begin(), targetBucket->end(),
                  [&key](const std::pair<K, V>& element) { return element.first == key; });
    if(present != targetBucket->end())
    {
        // Entry exists - switch to a new value
        present->second = value;
    }
    else
    {
        targetBucket->push_back(entry);
    }

    ++size_;
    if(size_) isEmpty_ = false;

    // Each time a hash is inserted it the calculation be made analyizing the ratio of existing keys and occupied buckets
    // If the ratio is will be greater than 1.25 or lower than 0.75 the hash table will have to be resized - to either size * 2 or size / 2
    std::cout << "DBG: Load factor before if " << static_cast<float>(loadFactor()) << std::endl;
    if(float lf = loadFactor() > 0.75)
    {
        std::cout << "DBG: Load factor = " << lf << std::endl;
        resize(resizeVariant::grow);
    }

    std::cout << "DBG: size_ = " << size_ << " isEmpty_ = " << std::boolalpha << isEmpty_ << " hashingRange_ = " << hashingRange_ << std::endl; 
    return;
}

template<typename K, typename V>
void HashTable<K, V>::remove(const K& key)
{
    auto targetBucket = getBucket(key);

    // Check if a given entry exists
    auto present = std::find_if(targetBucket->begin(), targetBucket->end(),
                  [&key](const std::pair<K, V>& element) { return element.first == key; });
    if(present != targetBucket->end())
    {
        targetBucket->erase(present);
        std::cout << "Deleted specified key from the hash table" << std::endl;

        --size_;
        if(!size_) isEmpty_ = true; 

        // Check if resize is needed
        if(float lf = loadFactor() > 1.25)
        {
            resize(resizeVariant::shrink);
        }

        std::cout << "DBG: size_ = " << size_ << " isEmpty_ = " << std::boolalpha << isEmpty_ << " hashingRange_ = " << hashingRange_ << std::endl; 
        return;
    }

    std::cout << "No entry with given key was found" << std::endl;
    std::cout << "DBG: size_ = " << size_ << " isEmpty_ = " << std::boolalpha << isEmpty_ << " hashingRange_ = " << hashingRange_ << std::endl; 
}

template<typename K, typename V>
bucket<K, V>* HashTable<K, V>::getBucket(const K& key)
{
    return &table_[calculateHash(key, hashingRange_)];
}


/// @brief Returns a pointer-to-bucket with specified key
/// @tparam K key type
/// @tparam V value type
/// @param key key value
/// @return Valid bucket pointer if found, nullptr if not found
template<typename K, typename V>
std::pair<K, V>* HashTable<K, V>::getBucketEntry(const K& key)
{
    auto targetBucket = getBucket(key);
    auto present = std::find_if(targetBucket->begin(), targetBucket->end(),
                  [&key](const std::pair<K, V>& element) { return element.first == key; });

    if(present != targetBucket->end()) return &(*present);
    return nullptr;
}

/// @brief Checks if a given hash table contains a entry with specified key
/// @tparam K key type
/// @tparam V value type
/// @param key key value
/// @return true if given key was found, false if not
template<typename K, typename V>
bool HashTable<K, V>::contain(const K& key)
{
    return getBucketEntry(key);
}

/// @brief Will parse each bucket displaying size of it
/// @note This function was mainly used for testing and if 
template <typename K, typename V>
void HashTable<K, V>::showStatus(std::ostream& os) const
{
    os << "DBG: Parsing Start\n";

    for(size_t currentHash = 0; currentHash < table_.size(); currentHash++)
    {
        os << "Hash[" << currentHash << "] => ";
        
        if(table_[currentHash].empty())
        {
            os << "*Empty*\n";
        }
        else
        {
            os << "bucket size: " << table_[currentHash].size();

            #ifdef DBG_MODE
            os << " => ";
            for(auto entry : table_[currentHash])
            {
                os << "[" << entry.first << ", " << entry.second << "] - ";
            }
            os << " *end*";
            #endif
            os << "\n";
        }
    }
    os << "DBG: Parsing Stop\n";
}


// Just for now
template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    for(auto hash : table_)
    {
        hash.clear();
    }

    table_.clear();
}

#endif