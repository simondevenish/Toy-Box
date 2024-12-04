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
#include <cstring> // For memcpy, strlen

namespace toybox
{
namespace utils
{
namespace data_structures
{
struct DynamicString {
private:
    char* data; 
    size_t size;
    size_t capacity;

    void Grow(size_t new_capacity);

public:
    // Constructor
    DynamicString();

    // Constructor from C-string
    DynamicString(const char* cstr);

    // Copy constructor
    DynamicString(const DynamicString& other);

    // Move constructor
    DynamicString(DynamicString&& other) noexcept;

    // Copy assignment operator
    DynamicString& operator=(const DynamicString& other);

    // Move assignment operator
    DynamicString& operator=(DynamicString&& other) noexcept;


    // Equality comparison
    bool operator==(const DynamicString& other) const;

    // Inequality comparison
    bool operator!=(const DynamicString& other) const;

    // Append operator
    DynamicString& operator+=(const DynamicString& other);

    // Subscript operator
    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    // Destructor
    ~DynamicString();

    // Get the length of the string
    size_t Length() const;

    // Get the capacity of the string
    size_t Capacity() const;

    // Append another string
    void Append(const DynamicString& other);

    // Append a C-string
    void Append(const char* cstr);

    // Clear the string
    void Clear();

    // Resize the string (adjust capacity)
    void Resize(size_t new_capacity);

    // Access character at index (returns true on success, false on failure)
    bool At(size_t index, char* out_char) const;

    // Get C-string representation
    const char* CStr() const;

    // Check if the string is empty
    bool Empty() const;
};

} // namespace data_structures
} // namespace utils
} // namespace toybox
