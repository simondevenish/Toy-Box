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