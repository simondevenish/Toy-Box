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
    return reinterpret_cast<size_t>(&key) % capacity;
}

template<typename Key, typename Value>
size_t HashMap<Key, Value>::Probe(size_t index) const {
    return (index + 1) % capacity;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::Insert(const Key& key, const Value& value) {
    if (size >= capacity * 0.7) {
        Resize(capacity * 2);
    }

    size_t index = Hash(key);
    while (table[index].occupied) {
        if (table[index].key == key) {
            table[index].value = value;
            return;
        }
        index = Probe(index);
    }

    table[index].key = key;
    table[index].value = value;
    table[index].occupied = true;
    ++size;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::Remove(const Key& key) {
    size_t index = Hash(key);
    while (table[index].occupied) {
        if (table[index].key == key) {
            table[index].occupied = false;
            --size;
            return;
        }
        index = Probe(index);
    }
}

template<typename Key, typename Value>
Value* HashMap<Key, Value>::Find(const Key& key) {
    size_t index = Hash(key);
    while (table[index].occupied) {
        if (table[index].key == key) {
            return &table[index].value;
        }
        index = Probe(index);
    }
    return nullptr;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::Contains(const Key& key) const {
    size_t index = Hash(key);
    while (table[index].occupied) {
        if (table[index].key == key) {
            return true;
        }
        index = Probe(index);
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