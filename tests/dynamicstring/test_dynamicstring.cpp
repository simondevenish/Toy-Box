#include <gtest/gtest.h>
#include "dynamicstring.h"

using namespace toybox::utils::data_structures;

TEST(DynamicStringTests, DefaultConstructor) {
    DynamicString str;
    EXPECT_EQ(str.Length(), 0);
    EXPECT_TRUE(str.Empty());
}

TEST(DynamicStringTests, CStrAndLength) {
    DynamicString str("Test");
    EXPECT_EQ(str.Length(), 4);
    EXPECT_STREQ(str.CStr(), "Test");
}

TEST(DynamicStringTests, AppendAndAccess) {
    DynamicString str("Hello");
    str.Append(", World!");
    EXPECT_EQ(str.Length(), 13);
    EXPECT_STREQ(str.CStr(), "Hello, World!");
}

TEST(DynamicStringTests, AppendCStr) {
    DynamicString str("Hello");
    str.Append(" there!");
    EXPECT_EQ(str.Length(), 12);
    EXPECT_STREQ(str.CStr(), "Hello there!");
}

TEST(DynamicStringTests, Clear) {
    DynamicString str("Test");
    str.Clear();
    EXPECT_EQ(str.Length(), 0);
    EXPECT_STREQ(str.CStr(), "");
}

TEST(DynamicStringTests, CopyConstructor) {
    DynamicString str1("CopyTest");
    DynamicString str2(str1);
    EXPECT_EQ(str2.Length(), str1.Length());
    EXPECT_STREQ(str2.CStr(), str1.CStr());
}

TEST(DynamicStringTests, MoveConstructor) {
    DynamicString str1("MoveTest");
    DynamicString str2(std::move(str1));
    EXPECT_STREQ(str2.CStr(), "MoveTest");
    EXPECT_EQ(str1.Length(), 0);
    EXPECT_TRUE(str1.Empty());
}

TEST(DynamicStringTests, CopyAssignmentOperator) {
    DynamicString str1("AssignTest");
    DynamicString str2;
    str2 = str1;
    EXPECT_EQ(str2.Length(), str1.Length());
    EXPECT_STREQ(str2.CStr(), str1.CStr());
}

TEST(DynamicStringTests, MoveAssignmentOperator) {
    DynamicString str1("MoveAssignTest");
    DynamicString str2;
    str2 = std::move(str1);
    EXPECT_STREQ(str2.CStr(), "MoveAssignTest");
    EXPECT_EQ(str1.Length(), 0);
    EXPECT_TRUE(str1.Empty());
}

TEST(DynamicStringTests, EqualityComparison) {
    DynamicString str1("Test");
    DynamicString str2("Test");
    EXPECT_TRUE(str1 == str2);
    DynamicString str3("Different");
    EXPECT_TRUE(str1 != str3);
}

TEST(DynamicStringTests, SubscriptOperator) {
    DynamicString str("Subscript");
    EXPECT_EQ(str[0], 'S');
    EXPECT_EQ(str[1], 'u');
    EXPECT_EQ(str[8], 't');
}

TEST(DynamicStringTests, AtMethod) {
    DynamicString str("Access");
    char c;
    EXPECT_TRUE(str.At(0, &c));
    EXPECT_EQ(c, 'A');
    EXPECT_TRUE(str.At(3, &c));
    EXPECT_EQ(c, 'e');
    EXPECT_FALSE(str.At(10, &c));
}


TEST(DynamicStringTests, CapacityAndResize) {
    DynamicString str("Test");
    size_t initial_capacity = str.Capacity();
    str.Resize(initial_capacity + 10);
    EXPECT_GT(str.Capacity(), initial_capacity);
    str.Append("!");
    EXPECT_EQ(str.Length(), 5);
}

TEST(DynamicStringTests, AppendOperator) {
    DynamicString str1("Hello");
    DynamicString str2(", World!");
    str1 += str2;
    EXPECT_STREQ(str1.CStr(), "Hello, World!");
    EXPECT_EQ(str1.Length(), 13);
}

TEST(DynamicStringTests, EmptyCheck) {
    DynamicString str;
    EXPECT_TRUE(str.Empty());
    str.Append("NotEmpty");
    EXPECT_FALSE(str.Empty());
}

TEST(DynamicStringTests, GrowAndShrink) {
    DynamicString str("GrowShrink");
    size_t initial_capacity = str.Capacity();
    str.Resize(initial_capacity + 10);
    EXPECT_GT(str.Capacity(), initial_capacity);
    str.Clear();
    str.Resize(5);
    EXPECT_GE(str.Capacity(), 5);
    EXPECT_EQ(str.Length(), 0);
}

TEST(DynamicStringTests, AppendEmpty) {
    DynamicString str1("NonEmpty");
    DynamicString str2;
    str1.Append(str2);
    EXPECT_STREQ(str1.CStr(), "NonEmpty");
    EXPECT_EQ(str1.Length(), 8);
}
