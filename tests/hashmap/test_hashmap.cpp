#include <gtest/gtest.h>
#include "hashmap.h"

using namespace toybox::utils::data_structures;

TEST(HashMapTests, DefaultConstructor) {
    HashMap<int, const char*> map;
    EXPECT_EQ(map.Size(), 0);
    EXPECT_TRUE(map.Empty());
}

TEST(HashMapTests, InsertAndRetrieve) {
    HashMap<int, const char*> map;
    map.Insert(1, "one");
    map.Insert(2, "two");

    EXPECT_EQ(map.Size(), 2);

    const char** value_ptr = map.Find(1);
    ASSERT_NE(value_ptr, nullptr);
    EXPECT_STREQ(*value_ptr, "one");

    value_ptr = map.Find(2);
    ASSERT_NE(value_ptr, nullptr);
    EXPECT_STREQ(*value_ptr, "two");
}

TEST(HashMapTests, ContainsAndRemove) {
    HashMap<int, const char*> map;
    map.Insert(1, "one");
    map.Insert(2, "two");

    EXPECT_TRUE(map.Contains(1));
    EXPECT_TRUE(map.Contains(2));

    map.Remove(1);
    EXPECT_FALSE(map.Contains(1));
    EXPECT_TRUE(map.Contains(2));
    EXPECT_EQ(map.Size(), 1);
}

TEST(HashMapTests, Resize) {
    HashMap<int, const char*> map;

    for (int i = 0; i < 20; ++i) {
        map.Insert(i, "value");
    }

    EXPECT_EQ(map.Size(), 20);
    for (int i = 0; i < 20; ++i) {
        EXPECT_TRUE(map.Contains(i));
    }
}

TEST(HashMapTests, FindNonExistentKey) {
    HashMap<int, const char*> map;
    map.Insert(1, "one");
    EXPECT_EQ(map.Find(2), nullptr); // Key 2 does not exist
}

TEST(HashMapTests, Clear) {
    HashMap<int, const char*> map;
    map.Insert(1, "one");
    map.Insert(2, "two");

    EXPECT_EQ(map.Size(), 2);
    map.Clear();
    EXPECT_EQ(map.Size(), 0);
    EXPECT_FALSE(map.Contains(1));
    EXPECT_FALSE(map.Contains(2));
}

TEST(HashMapTests, OverwriteValue) {
    HashMap<int, const char*> map;
    map.Insert(1, "one");
    EXPECT_STREQ(*map.Find(1), "one");

    map.Insert(1, "ONE");
    EXPECT_STREQ(*map.Find(1), "ONE");
    EXPECT_EQ(map.Size(), 1); // Size shouldn't change for overwrite
}

TEST(HashMapTests, ProbeAndResolveCollision) {
    struct SimpleHash {
        size_t operator()(int key) const { return key % 10; }
    };

    HashMap<int, const char*> map(10);

    // Force collisions with keys that hash to the same bucket
    map.Insert(1, "one");
    map.Insert(11, "eleven");

    EXPECT_EQ(map.Size(), 2);
    EXPECT_STREQ(*map.Find(1), "one");
    EXPECT_STREQ(*map.Find(11), "eleven");

    map.Remove(1);
    EXPECT_FALSE(map.Contains(1));
    EXPECT_STREQ(*map.Find(11), "eleven");
}

TEST(HashMapTests, LargeResize) {
    HashMap<int, const char*> map(4);

    for (int i = 0; i < 100; ++i) {
        map.Insert(i, "value");
    }

    EXPECT_EQ(map.Size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(map.Contains(i));
    }
}

TEST(HashMapTests, CheckEmptyAfterClear) {
    HashMap<int, const char*> map;
    map.Insert(1, "one");
    map.Clear();
    EXPECT_TRUE(map.Empty());
    EXPECT_EQ(map.Size(), 0);
}

TEST(HashMapTests, ReinsertAfterRemove) {
    HashMap<int, const char*> map;
    map.Insert(1, "one");
    map.Remove(1);
    EXPECT_FALSE(map.Contains(1));

    map.Insert(1, "new_one");
    EXPECT_TRUE(map.Contains(1));
    EXPECT_STREQ(*map.Find(1), "new_one");
}

TEST(HashMapTests, ComplexKeyAndValue) {
    HashMap<std::string, std::string> map;

    map.Insert("key1", "value1");
    map.Insert("key2", "value2");

    EXPECT_EQ(map.Size(), 2);
    EXPECT_STREQ(map.Find("key1")->c_str(), "value1");
    EXPECT_STREQ(map.Find("key2")->c_str(), "value2");

    map.Remove("key1");
    EXPECT_FALSE(map.Contains("key1"));
    EXPECT_TRUE(map.Contains("key2"));
}
