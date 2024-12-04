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

template<typename T>
struct DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    // Constructor
    DynamicArray(size_t initial_capacity = 4)
        : data(static_cast<T*>(malloc(initial_capacity * sizeof(T)))),
          size(0),
          capacity(initial_capacity) {}

    // Copy constructor
    DynamicArray(const DynamicArray& other);

    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept;

    // Copy assignment constructor
    DynamicArray& operator=(const DynamicArray& other);

    // Move assignment constructor
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    ~DynamicArray() {
        Clear();
        free(data);
    }

    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

    void PushBack(const T& value);

    void PopBack();

    T* Data() const;

    T& Front() const;

    T& Back() const;

    size_t Size() const;

    bool Empty() const;

    bool Contains(const T& value) const;

    void Reserve(size_t new_capacity);

    void Insert(size_t index, const T& value);

    void Reset();

    void Clear();

    template<typename Predicate>
    void RemoveIf(Predicate pred);

    void ReserveAndInitialize(size_t new_capacity, const T& default_value);

    size_t Find(const T& value) const;

    void Reverse();

    DynamicArray Slice(size_t start, size_t end) const;

    void Extend(const DynamicArray& other);

    void ShrinkToFit();

    void Resize(size_t new_size);

    void Swap(DynamicArray& other);

    void Assign(size_t count, const T& value);

    void Remove(const T& value);

    void SwapElements(size_t index1, size_t index2);

    size_t Capacity() const;
    void Fill(const T& value);

    template<typename Comparator>
    void Sort(Comparator comp);

    void Append(const DynamicArray& other);

    template<typename Callable>
    void ForEach(Callable func) const;

    template<typename... Args>
    void EmplaceAt(size_t index, Args&&... args);

    T* begin() { return data; }
    T* end() { return data + size; }
    const T* begin() const { return data; }
    const T* end() const { return data + size; }

    T& At(size_t index);
    const T& At(size_t index) const;
};
} // namespace data_structures
} // namespace utils
} // namespace toybox

#include "dynamicarray.inl"