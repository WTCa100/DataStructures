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
    const size_t minimalRange_;
    size_t size_;
    bool isEmpty_;
    std::vector<bucket<K, V>> table_;
    bool allowDynamicHashing_;

    size_t calculateHash(const K& key, const size_t& range) const;
    float loadFactor();
    bool resize(resizeVariant variant);
    
    // We generally don't want to give the user power to alter the contents of given buckets and it's values
    // It will be switched later on so that the getBucketPtr/-Entry will return pointer from private function

    /// @brief Returns an mutable pointer to a bucket where the entry with given key is assumed to be located
    /// @param key key value
    /// @return table[hashKey] where hashKey is equal to hash calculated from the key
    /// @note it is not guranteed that a desired key will be located in a given bucket, it will just calculate the hash and assume
    /// that the value shall be located in a given bucket
    bucket<K, V>* getBucketPtr(const K& key) { return getBucketPtr(calculateHash(key, hashingRange_)); }

    bucket<K, V>* getBucketPtr(const size_t& index);


    /// @brief Returns an mutable pointer to a pair with given key from the hash table
    /// @param key key value
    /// @return pointer to pair with key, nullptr if no entry exists
    std::pair<K, V>* getBucketEntryPtr(const K& key);
public:
    HashTable() = delete;
    HashTable(size_t hashRange) : HashTable(hashRange, false) {}
    HashTable(size_t hashRange, bool dynamicHashingFlag);
    ~HashTable();

    void insert(const K& key, const V& value);
    void insert(const std::pair<K, V>& value);
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

    #ifdef DBG_MODE
    inline bool DBG_resize() { return resize(resizeVariant::grow); }
    inline size_t DBG_calculateHash(const K& key) { return calculateHash(key, hashingRange_); }
    #endif

    V* getValue(const K& key);

    /// @brief Returns an immutable refference to a bucket where the entry with given key is assumed to be located
    /// @param key key value
    /// @return refference to table[hashKey] where hashKey is equal to hash calculated from the key
    /// @note it is not guranteed that a desired key will be located in a given bucket, it will just calculate the hash and assume
    /// that the value shall be located in a given bucket
    const bucket<K, V>& getBucket(const K& key) const { return getBucket(calculateHash(key, hashingRange_)); }

    /// @brief Returns an immutable refference to a bucket on a given index
    /// @param index index value 
    /// @return const refference to a given bucket
    /// @warning This function can get out of bound resulting in undefined behavior
    const bucket<K, V>& getBucket(const size_t& index) const { return table_[index]; }

    const std::pair<K, V>& getBucketEntry(const K& key) const;
};

// In order for the compiler and linker to correctly handle this type of files we need to include class function definitions
// in the same translation unit so that the linker can correctly handle definition linkage.

/// @brief Basic constructor for the hash table, it will reserve the space of hashRange number of buckets.
/// @tparam K key type
/// @tparam V value type
/// @param hashRange ammount of initial buckets and minimal range for later resize
/// @param dynamicHashingFlag specified if dynamic resize shall be used while removing or inserting values
/// @warning hashRange shall have a non-zero value, the constructor will throw an runtime error when condition is not met
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t hashRange, bool dynamicHashingFlag) : minimalRange_(hashRange)
{
    if(hashRange == 0) throw std::runtime_error("Invalid hash table initial size. Use non-zero value only");

    table_.reserve(hashRange);
    hashingRange_ = hashRange;
    
    // Initialize table with empty buckets
    for(size_t i = 0; i < hashingRange_; i++)
    {
        bucket<K, V> currentBucket;
        table_.push_back(currentBucket);
    }
    size_                = 0;
    isEmpty_             = true;
    allowDynamicHashing_ = dynamicHashingFlag;
}

template <typename K, typename V>
size_t HashTable<K, V>::calculateHash(const K& key, const size_t& range) const
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
    // if(size_ == 0 || size_ == 1)
    // {
    //     throw std::runtime_error("This resize should not happen - size = 0 or 1");
    // }

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
    insert(std::make_pair(key, value));
}

template <typename K, typename V>
void HashTable<K, V>::insert(const std::pair<K, V>& value)
{
    K key = value.first;
    auto targetBucket = getBucketPtr(key);
    
    // Check if a given entry (key) already exists on a given bucket
    auto present = std::find_if(targetBucket->begin(), targetBucket->end(),
                  [&key](const std::pair<K, V>& element) { return element.first == key; });
    if(present != targetBucket->end())
    {
        // Entry exists - switch to a new value
        present->second = value.second;
    }
    else
    {
        targetBucket->push_back(value);
    }

    ++size_;
    if(size_) isEmpty_ = false;

    // Each time a hash is inserted it the calculation be made analyizing the ratio of existing keys and occupied buckets
    // If the ratio is will be greater than 1.25 or lower than 0.75 the hash table will have to be resized - to either size * 2 or size / 2
    if(float lf = loadFactor() > 0.75 && allowDynamicHashing_)
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
    auto targetBucket = getBucketPtr(key);

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
        // We will never get below the minimal hashing range, as we only grow the hash table multiplying it by 2 and then dividing it by 2
        if(float lf = loadFactor() < 0.25 && allowDynamicHashing_ && hashingRange_ > minimalRange_)
        {
            resize(resizeVariant::shrink);
        }

        std::cout << "DBG: size_ = " << size_ << " isEmpty_ = " << std::boolalpha << isEmpty_ << " hashingRange_ = " << hashingRange_ << std::endl; 
        return;
    }
    else
    {
        std::cout << "No value with given key was found\n";
    }

    std::cout << "No entry with given key was found" << std::endl;
    std::cout << "DBG: size_ = " << size_ << " isEmpty_ = " << std::boolalpha << isEmpty_ << " hashingRange_ = " << hashingRange_ << std::endl; 
}

template<typename K, typename V>
bucket<K, V>* HashTable<K, V>::getBucketPtr(const size_t& index)
{
    return &table_[index];
}


/// @brief Returns a pointer to pair with specified key
/// @tparam K key type
/// @tparam V value type
/// @param key key value
/// @return Valid bucket pointer if found, nullptr if not found
template<typename K, typename V>
std::pair<K, V>* HashTable<K, V>::getBucketEntryPtr(const K& key)
{
    auto targetBucket = getBucketPtr(key);
    auto present = std::find_if(targetBucket->begin(), targetBucket->end(),
                  [&key](const std::pair<K, V>& element) { return element.first == key; });

    // We will probably never get here, its to surpress the -Werror=attributes
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
    return getBucketEntryPtr(key);
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

/// @brief Returns an mutable pointer to value if found.
/// @tparam K key type
/// @tparam V value type
/// @param key key value
/// @return pointer to value or nullptr if no value was found
template<typename K, typename V>
V* HashTable<K, V>::getValue(const K& key)
{
    if(std::pair<K, V>* get = getBucketEntryPtr(key)) return &(get->second);
    return nullptr;
}

/// @brief Will return a copy of a pair with given key if found. Returns nullptr if the value was not found withing the table
/// @tparam K key type
/// @tparam V value type
/// @param key key value
/// @return Copy of a pair with given key provided that exists
template<typename K, typename V>
const std::pair<K, V>& HashTable<K, V>::getBucketEntry(const K& key) const
{
    auto present = std::find_if(getBucket(key).begin(), getBucket(key).end(),
                  [&key](const std::pair<K, V>& element) { return element.first == key; });
    if(present != getBucket(key).end()) return *present;

    /* Due to implementation limitation this function will have to throw an error if no entry is found with a given key.
       I wanted to make this function to work similar to i.e. std::find(), that will some form of invalid an uqnie entry
       if no entry with key is found - however since ths find_if returns an iterator to a vector it will not be possible
       to refference it back into the const std::pair<K, V>& const as the returned address will be pointing at the vector
       iterator and not the actual std::pair entry*/
    throw std::runtime_error("No entry with given key was found - first check, then get!");
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