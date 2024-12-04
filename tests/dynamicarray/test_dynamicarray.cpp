#include <gtest/gtest.h>
#include "dynamicarray.h"

using namespace toybox::utils::data_structures;

TEST(DynamicArrayTests, DefaultConstructor) {
    DynamicArray<int> array;
    EXPECT_EQ(array.Size(), 0);
    EXPECT_TRUE(array.Empty());
}

TEST(DynamicArrayTests, PushBackAndAccess) {
    DynamicArray<int> array;
    array.PushBack(10);
    array.PushBack(20);
    EXPECT_EQ(array.Size(), 2);
    EXPECT_EQ(array.At(0), 10);
    EXPECT_EQ(array.At(1), 20);
}

TEST(DynamicArrayTests, Remove) {
    DynamicArray<int> array;
    array.PushBack(10);
    array.PushBack(20);
    array.Remove(10);
    EXPECT_EQ(array.Size(), 1);
    EXPECT_EQ(array.At(0), 20);
}

TEST(DynamicArrayTests, ResizeAndAccess) {
    DynamicArray<int> array;
    array.Resize(5);
    EXPECT_EQ(array.Size(), 5);
    for (size_t i = 0; i < array.Size(); ++i) {
        EXPECT_EQ(array.At(i), 0);
    }
}

TEST(DynamicArrayTests, FindAndContains) {
    DynamicArray<int> array;
    array.PushBack(10);
    array.PushBack(20);
    EXPECT_TRUE(array.Contains(10));
    EXPECT_EQ(array.Find(20), 1);
    EXPECT_EQ(array.Find(30), static_cast<size_t>(-1));
}

TEST(DynamicArrayTests, ReserveAndCapacity) {
    DynamicArray<int> array;
    array.Reserve(10);
    EXPECT_EQ(array.Capacity(), 10);
    EXPECT_EQ(array.Size(), 0);
    array.PushBack(5);
    EXPECT_EQ(array.Size(), 1);
}

TEST(DynamicArrayTests, FrontAndBack) {
    DynamicArray<int> array;
    array.PushBack(10);
    array.PushBack(20);
    EXPECT_EQ(array.Front(), 10);
    EXPECT_EQ(array.Back(), 20);
}

TEST(DynamicArrayTests, ShrinkToFit) {
    DynamicArray<int> array;
    array.Reserve(10);
    array.PushBack(5);
    array.PushBack(15);
    array.ShrinkToFit();
    EXPECT_EQ(array.Capacity(), array.Size());
}

TEST(DynamicArrayTests, Reverse) {
    DynamicArray<int> array;
    array.PushBack(1);
    array.PushBack(2);
    array.PushBack(3);
    array.Reverse();
    EXPECT_EQ(array.At(0), 3);
    EXPECT_EQ(array.At(1), 2);
    EXPECT_EQ(array.At(2), 1);
}

TEST(DynamicArrayTests, ClearAndReset) {
    DynamicArray<int> array;
    array.PushBack(1);
    array.PushBack(2);
    EXPECT_EQ(array.Size(), 2);
    array.Clear();
    EXPECT_EQ(array.Size(), 0);
    EXPECT_TRUE(array.Empty());
    array.Reset();
    EXPECT_EQ(array.Capacity(), 0);
    EXPECT_TRUE(array.Empty());
}

TEST(DynamicArrayTests, Assign) {
    DynamicArray<int> array;
    array.Assign(5, 42);
    EXPECT_EQ(array.Size(), 5);
    for (size_t i = 0; i < array.Size(); ++i) {
        EXPECT_EQ(array.At(i), 42);
    }
}

TEST(DynamicArrayTests, Sort) {
    DynamicArray<int> array;
    array.PushBack(3);
    array.PushBack(1);
    array.PushBack(2);
    array.Sort([](int a, int b) { return a < b; });
    EXPECT_EQ(array.At(0), 1);
    EXPECT_EQ(array.At(1), 2);
    EXPECT_EQ(array.At(2), 3);
}

TEST(DynamicArrayTests, Extend) {
    DynamicArray<int> array1;
    array1.PushBack(1);
    array1.PushBack(2);
    DynamicArray<int> array2;
    array2.PushBack(3);
    array2.PushBack(4);
    array1.Extend(array2);
    EXPECT_EQ(array1.Size(), 4);
    EXPECT_EQ(array1.At(2), 3);
    EXPECT_EQ(array1.At(3), 4);
}

TEST(DynamicArrayTests, Append) {
    DynamicArray<int> array;
    DynamicArray<int> to_append;
    to_append.PushBack(1);
    to_append.PushBack(2);
    array.Append(to_append);
    EXPECT_EQ(array.Size(), 2);
    EXPECT_EQ(array.At(0), 1);
    EXPECT_EQ(array.At(1), 2);
}

TEST(DynamicArrayTests, Swap) {
    DynamicArray<int> array1;
    DynamicArray<int> array2;
    array1.PushBack(1);
    array1.PushBack(2);
    array2.PushBack(3);
    array2.PushBack(4);
    array1.Swap(array2);
    EXPECT_EQ(array1.Size(), 2);
    EXPECT_EQ(array1.At(0), 3);
    EXPECT_EQ(array2.Size(), 2);
    EXPECT_EQ(array2.At(0), 1);
}

TEST(DynamicArrayTests, RemoveIf) {
    DynamicArray<int> array;
    array.PushBack(1);
    array.PushBack(2);
    array.PushBack(3);
    array.RemoveIf([](int x) { return x % 2 == 0; }); // Remove even numbers
    EXPECT_EQ(array.Size(), 2);
    EXPECT_EQ(array.At(0), 1);
    EXPECT_EQ(array.At(1), 3);
}
