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

namespace toybox
{
namespace utils
{
namespace data_structures
{

template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(size_t initial_capacity)
    : capacity(initial_capacity), size(0) {
    table = static_cast<Entry*>(malloc(capacity * sizeof(Entry)));
    if (!table) {
        // Handle memory allocation failure
        abort();
    }
    for (size_t i = 0; i < capacity; ++i) {
        table[i].occupied = false;
    }
}

template<typename Key, typename Value>
HashMap<Key, Value>::~HashMap() {
    Clear();
    free(table);
}

template<typename Key, typename Value>
size_t HashMap<Key, Value>::Hash(const Key& key) const {
    return HashTraits<Key>::Hash(key, capacity);
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::KeysEqual(const Key& key1, const Key& key2) const {
    return HashTraits<Key>::Equal(key1, key2);
}

template<typename Key, typename Value>
size_t HashMap<Key, Value>::Probe(size_t index) const {
    size_t original_index = index;
    do {
        // Check if the current slot is empty or a valid slot to return
        if (!table[index].occupied) {
            return index;
        }
        index = (index + 1) % capacity;
    } while (index != original_index); 

    return capacity; // Use capacity as a sentinel value for failure
}


template<typename Key, typename Value>
void HashMap<Key, Value>::Insert(const Key& key, const Value& value) {
    if (size >= capacity * 0.7) {
        Resize(capacity * 2);
    }

    size_t index = Hash(key);
    size_t original_index = index;
    while (table[index].occupied) {
        if (KeysEqual(table[index].key, key)) {
            table[index].value = value; // Update existing key
            return;
        }
        index = Probe(index);
        if (index == original_index) {
            // Table is full; should not happen due to resize logic
            return;
        }
    }

    table[index].key = key;
    table[index].value = value;
    table[index].occupied = true;
    ++size;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::Remove(const Key& key) {
    size_t index = Hash(key);
    size_t original_index = index;
    while (table[index].occupied) {
        if (KeysEqual(table[index].key, key)) {
            table[index].occupied = false;
            --size;
            return;
        }
        index = Probe(index);
        if (index == original_index) {
            // Key not found
            return;
        }
    }
}

template<typename Key, typename Value>
Value* HashMap<Key, Value>::Find(const Key& key) {
    size_t index = Hash(key);
    size_t original_index = index;
    while (table[index].occupied) {
        if (KeysEqual(table[index].key, key)) {
            return &table[index].value;
        }
        index = Probe(index);
        if (index == original_index) {
            break; // Key not found
        }
    }
    return nullptr;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::Contains(const Key& key) const {
    size_t index = Hash(key);
    size_t original_index = index;
    while (table[index].occupied) {
        if (KeysEqual(table[index].key, key)) {
            return true;
        }
        index = Probe(index);
        if (index == original_index) {
            break; // Key not found
        }
    }
    return false;
}

template<typename Key, typename Value>
size_t HashMap<Key, Value>::Size() const {
    return size;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::Empty() const {
    return size == 0;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::Clear() {
    for (size_t i = 0; i < capacity; ++i) {
        if (table[i].occupied) {
            table[i].occupied = false;
        }
    }
    size = 0;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::Resize(size_t new_capacity) {
    Entry* old_table = table;
    size_t old_capacity = capacity;

    capacity = new_capacity;
    table = static_cast<Entry*>(malloc(capacity * sizeof(Entry)));
    if (!table) {
        abort();
    }
    for (size_t i = 0; i < capacity; ++i) {
        table[i].occupied = false;
    }

    size = 0;
    for (size_t i = 0; i < old_capacity; ++i) {
        if (old_table[i].occupied) {
            Insert(old_table[i].key, old_table[i].value);
        }
    }

    free(old_table);
}

} // namespace data_structures
} // namespace utils
} // namespace toybox