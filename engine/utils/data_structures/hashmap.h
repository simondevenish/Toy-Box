/*
 * Toy Box: A Creative Engine for Imaginative and Quirky Games
 *
 * Licensed under the GNU General Public License, Version 3.
 * For license details, visit: https://www.gnu.org/licenses/gpl-3.0.html
 *
 * Questions or contributions? Reach out to Simon Devenish:
 * simon.devenish@outlook.com
 */

#pragma once

#include <cstddef> // For size_t
#include <cstdlib> // For malloc, free
#include <cstring> // For strcmp

#include "dynamicstring.h"

namespace toybox
{
namespace utils
{
namespace data_structures
{

// Default HashTraits for general types (e.g., integers)
template<typename Key>
struct HashTraits {
    static size_t Hash(const Key& key, size_t capacity) {
        return static_cast<size_t>(key) % capacity;
    }

    static bool Equal(const Key& key1, const Key& key2) {
        return key1 == key2;
    }
};

// Specialization of HashTraits for const char* keys
template<>
struct HashTraits<const char*> {
    static size_t Hash(const char* key, size_t capacity) {
        unsigned long hash = 5381;
        int c;
        const char* str = key;
        while ((c = *str++)) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % capacity;
    }

    static bool Equal(const char* key1, const char* key2) {
        return strcmp(key1, key2) == 0;
    }
};

// Specialization of HashTraits for DynamicString
template<>
struct HashTraits<DynamicString> {
    static size_t Hash(const DynamicString& key, size_t capacity) {
        unsigned long hash = 5381;
        for (size_t i = 0; i < key.Length(); ++i) {
            char c = key[i];
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % capacity;
    }

    static bool Equal(const DynamicString& key1, const DynamicString& key2) {
        return key1 == key2;
    }
};

template<typename Key, typename Value>
struct HashMap {
private:
    struct Entry {
        Key key;
        Value value;
        bool occupied;
    };

    Entry* table;
    size_t capacity;
    size_t size;

    // Hash function
    size_t Hash(const Key& key) const;

    // Probing for collisions
    size_t Probe(size_t index) const;

    // Key equality comparison
    bool KeysEqual(const Key& key1, const Key& key2) const;

public:
    // Constructor
    HashMap(size_t initial_capacity = 16);

    // Destructor
    ~HashMap();

    // Insert or update a key-value pair
    void Insert(const Key& key, const Value& value);

    // Remove a key-value pair
    void Remove(const Key& key);

    // Retrieve a value by key
    Value* Find(const Key& key);

    // Check if a key exists
    bool Contains(const Key& key) const;

    // Get the number of elements
    size_t Size() const;

    // Check if the map is empty
    bool Empty() const;

    // Clear all entries
    void Clear();

    // Resize the hashmap when capacity is exceeded
    void Resize(size_t new_capacity);
};

} // namespace data_structures
} // namespace utils
} // namespace toybox

#include "hashmap.inl"