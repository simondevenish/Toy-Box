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
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
: data(static_cast<T*>(malloc(other.capacity * sizeof(T)))),
    size(other.size),
    capacity(other.capacity) {
    for (size_t i = 0; i < size; ++i) {
        new (&data[i]) T(other.data[i]);
    }
}
template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
: data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this != &other) {
        Clear();
        free(data);

        data = static_cast<T*>(malloc(other.capacity * sizeof(T)));
        size = other.size;
        capacity = other.capacity;

        for (size_t i = 0; i < size; ++i) {
            new (&data[i]) T(other.data[i]);
        }
    }
    return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
        Clear();
        free(data);

        data = other.data;
        size = other.size;
        capacity = other.capacity;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

template<typename T>
bool DynamicArray<T>::operator==(const DynamicArray<T>& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

template<typename T>
bool DynamicArray<T>::operator!=(const DynamicArray<T>& other) const {
    return !(*this == other);
}

template<typename T>
void DynamicArray<T>::PushBack(const T& value) {
    if (size >= capacity)
        Reserve(capacity * 2);
    new (&data[size++]) T(value); // Copy-construct at the next position
}

template<typename T>
void DynamicArray<T>::PopBack() {
    if (size > 0) {
        data[--size].~T(); // Destroy the last element
    }
}

template<typename T>
T* DynamicArray<T>::Data() const {
    return data;
}

template<typename T>
T& DynamicArray<T>::Front() const {
    if (size == 0) abort();
    return data[0];
}

template<typename T>
T& DynamicArray<T>::Back() const {
    if (size == 0) abort();
    return data[size - 1];
}

template<typename T>
size_t DynamicArray<T>::Size() const {
    return size;
}

template<typename T>
bool DynamicArray<T>::Empty() const {
    return size == 0;
}

template<typename T>
bool DynamicArray<T>::Contains(const T& value) const {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] == value) return true;
    }
    return false;
}

template<typename T>
void DynamicArray<T>::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity) return;

    // Allocate new memory block
    T* new_data = static_cast<T*>(malloc(new_capacity * sizeof(T)));
    if (!new_data) abort(); // Handle memory allocation failure explicitly

    // Move elements manually
    for (size_t i = 0; i < size; ++i) {
        new (&new_data[i]) T(data[i]); // Use copy constructor to copy data
        data[i].~T();                 // Explicitly destroy the old element
    }

    // Free old memory
    free(data);

    // Update internal pointers and capacity
    data = new_data;
    capacity = new_capacity;
}

template<typename T>
void DynamicArray<T>::Insert(size_t index, const T& value) {
    if (index > size) return;

    // Ensure there is enough capacity
    if (size >= capacity) {
        Reserve((capacity > 0) ? capacity * 2 : 1);
    }

    // Shift elements to the right
    for (size_t i = size; i > index; --i) {
        new (&data[i]) T(data[i - 1]); // Copy construct the element to its new position
        data[i - 1].~T();             // Destroy the old element in its previous position
    }

    new (&data[index]) T(value); // Copy construct the new element in place
    ++size;
}

template<typename T>
void DynamicArray<T>::Reset() {
    Clear();
    free(data); 
    data = nullptr;
    capacity = 0;
}

template<typename T>
void DynamicArray<T>::Clear() {
    for (size_t i = 0; i < size; ++i) {
        data[i].~T();
    }
    size = 0;
}

template<typename T>
template<typename Predicate>
void DynamicArray<T>::RemoveIf(Predicate pred) {
    size_t new_size = 0;
    for (size_t i = 0; i < size; ++i) {
        if (!pred(data[i])) {
            if (new_size != i) {
                new (&data[new_size]) T(data[i]); // Copy data to the new position
                data[i].~T();                   // Destroy the old position
            }
            ++new_size;
        } else {
            data[i].~T(); // Destroy the element if predicate matches
        }
    }
    size = new_size;
}

template<typename T>
void DynamicArray<T>::ReserveAndInitialize(size_t new_capacity, const T& default_value) {
    Reserve(new_capacity);
    for (size_t i = size; i < new_capacity; ++i) {
        new (&data[i]) T(default_value);
    }
    size = new_capacity;
}
template<typename T>
size_t DynamicArray<T>::Find(const T& value) const {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] == value) {
            return i;
        }
    }
    return static_cast<size_t>(-1); // Return an invalid index if not found
}

template<typename T>
void DynamicArray<T>::Reverse() {
    for (size_t i = 0; i < size / 2; ++i) {
        T temp = data[i];
        data[i] = data[size - 1 - i];
        data[size - 1 - i] = temp;
    }
}

template<typename T>
DynamicArray<T> DynamicArray<T>::Slice(size_t start, size_t end) const {
    if (start >= size || end > size || start >= end) abort();

    DynamicArray slice(end - start);
    for (size_t i = start; i < end; ++i) {
        slice.PushBack(data[i]);
    }
    return slice;
}

template<typename T>
void DynamicArray<T>::Extend(const DynamicArray& other) {
    Reserve(size + other.size);
    for (size_t i = 0; i < other.size; ++i) {
        PushBack(other.data[i]);
    }
}

template<typename T>
void DynamicArray<T>::ShrinkToFit() {
    if (size == capacity) return;

    T* new_data = static_cast<T*>(malloc(size * sizeof(T)));
    if (!new_data) abort();

    // Move existing elements
    for (size_t i = 0; i < size; ++i) {
        new (&new_data[i]) T(data[i]);
        data[i].~T();
    }

    // Free old memory and update pointers
    free(data);
    data = new_data;
    capacity = size;
}

template<typename T>
void DynamicArray<T>::Resize(size_t new_size) {
    if (new_size < size) {
        // Shrink: Destroy excess elements
        for (size_t i = new_size; i < size; ++i) {
            data[i].~T();
        }
    } else if (new_size > capacity) {
        // Expand: Allocate more memory
        Reserve(new_size);
    }

    // Construct default initialized elements
    for (size_t i = size; i < new_size; ++i) {
        new (&data[i]) T();
    }

    size = new_size;
}

template<typename T>
void DynamicArray<T>::Swap(DynamicArray& other) {
    T* temp_data = other.data;
    size_t temp_size = other.size;
    size_t temp_capacity = other.capacity;

    other.data = data;
    other.size = size;
    other.capacity = capacity;

    data = temp_data;
    size = temp_size;
    capacity = temp_capacity;
}

template<typename T>
void DynamicArray<T>::Assign(size_t count, const T& value) {
    Clear();
    if (count > capacity) {
        Reserve(count);
    }
    for (size_t i = 0; i < count; ++i) {
        new (&data[i]) T(value);
    }
    size = count;
}

template<typename T>
size_t DynamicArray<T>::Capacity() const {
    return capacity;
}

template<typename T>
void DynamicArray<T>::Fill(const T& value) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = value;
    }
}

template<typename T>
template<typename Comparator>
void DynamicArray<T>::Sort(Comparator comp) {
    // Bubble sort sucks! Use better algorithm as O(n^2) is not the one
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (comp(data[j], data[i])) {
                SwapElements(i, j);
            }
        }
    }
}

template<typename T>
void DynamicArray<T>::Append(const DynamicArray<T>& other) {
    Reserve(size + other.size);
    for (size_t i = 0; i < other.size; ++i) {
        PushBack(other.data[i]);
    }
}

template<typename T>
template<typename Callable>
void DynamicArray<T>::ForEach(Callable func) const {
    for (size_t i = 0; i < size; ++i) {
        func(data[i]);
    }
}

template<typename T>
template<typename... Args>
void DynamicArray<T>::EmplaceAt(size_t index, Args&&... args) {
    if (index >= size) return; // Index out of bounds
    new (&data[index]) T(std::forward<Args>(args)...);
}

template<typename T>
void DynamicArray<T>::SwapElements(size_t index1, size_t index2) {
    if (index1 >= size || index2 >= size) return; // Index out of bounds
    T temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}

template<typename T>
T& DynamicArray<T>::At(size_t index) {
    if (index >= size) abort(); // Index out of bounds
    return data[index];
}

template<typename T>
const T& DynamicArray<T>::At(size_t index) const {
    if (index >= size) abort(); // Index out of bounds
    return data[index];
}

template<typename T>
void DynamicArray<T>::Remove(const T& value) {
    size_t index = Find(value);
    if (index == static_cast<size_t>(-1)) return; // Value not found

    // Shift elements to the left
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }

    // Destroy the last element and reduce size
    data[--size].~T();
}


} // namespace data_structures
} // namespace utils
} // namespace toybox