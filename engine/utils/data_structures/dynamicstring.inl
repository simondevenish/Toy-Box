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
#include <cassert> // For assertions

#include "dynamicstring.h"

namespace toybox
{
namespace utils
{
namespace data_structures
{
    
bool DynamicString::operator==(const DynamicString& other) const {
    if (size != other.size) return false;
    return memcmp(data, other.data, size) == 0;
}

bool DynamicString::operator!=(const DynamicString& other) const {
    return !(*this == other);
}


DynamicString& DynamicString::operator+=(const DynamicString& other) {
    Append(other);
    return *this;
}

char& DynamicString::operator[](size_t index) {
    return At(index);
}

const char& DynamicString::operator[](size_t index) const {
    return At(index);
}

void DynamicString::Grow(size_t new_capacity) {
    if (new_capacity <= capacity) return;

    char* new_data = static_cast<char*>(malloc(new_capacity));
    if (!new_data) abort();

    if (data) {
        memcpy(new_data, data, size);
        free(data);
    }

    data = new_data;
    capacity = new_capacity;
    data[size] = '\0';
}

DynamicString::DynamicString()
    : data(nullptr), size(0), capacity(0) {}

DynamicString::DynamicString(const char* cstr)
    : data(nullptr), size(0), capacity(0) {
    if (cstr) {
        size = strlen(cstr);
        Grow(size + 1);
        memcpy(data, cstr, size);
        data[size] = '\0';
    }
}

DynamicString::DynamicString(const DynamicString& other)
    : data(nullptr), size(other.size), capacity(other.capacity) {
    if (other.data) {
        data = static_cast<char*>(malloc(capacity));
        memcpy(data, other.data, size);
        data[size] = '\0';
    }
}

DynamicString::DynamicString(DynamicString&& other) noexcept
    : data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

DynamicString& DynamicString::operator=(const DynamicString& other) {
    if (this != &other) {
        Clear();
        size = other.size;
        Grow(other.capacity);
        if (other.data) {
            memcpy(data, other.data, size);
            data[size] = '\0';
        }
    }
    return *this;
}

DynamicString& DynamicString::operator=(DynamicString&& other) noexcept {
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

DynamicString::~DynamicString() {
    Clear();
    free(data);
}

size_t DynamicString::Length() const {
    return size;
}

size_t DynamicString::Capacity() const {
    return capacity;
}

void DynamicString::Append(const DynamicString& other) {
    if (other.size == 0) return;

    Grow(size + other.size + 1);
    memcpy(data + size, other.data, other.size);
    size += other.size;
    data[size] = '\0';
}

void DynamicString::Append(const char* cstr) {
    if (!cstr) return;

    size_t cstr_len = strlen(cstr);
    Grow(size + cstr_len + 1);
    memcpy(data + size, cstr, cstr_len);
    size += cstr_len;
    data[size] = '\0';
}

void DynamicString::Clear() {
    size = 0;
    if (data) {
        data[0] = '\0'; // Null-terminate
    }
}

void DynamicString::Resize(size_t new_capacity) {
    Grow(new_capacity);
}

char& DynamicString::At(size_t index) {
    assert(index < size && "Index out of bounds");
    return data[index];
}

const char& DynamicString::At(size_t index) const {
    assert(index < size && "Index out of bounds");
    return data[index];
}

const char* DynamicString::CStr() const {
    return data ? data : "";
}

bool DynamicString::Empty() const {
    return size == 0;
}
}
}
}