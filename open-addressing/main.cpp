#include <gtest/gtest.h>
#include "hashmap.hpp"

// basic construction
TEST(HashMapTests, StartsEmptyDoesNotContain) {
    HashMap map(8);
    EXPECT_FALSE(map.contains(1));
}

// insert and lookup
TEST(HashMapTests, InsertThenContainsAndAt) {
    HashMap map(8);
    EXPECT_TRUE(map.insert(10, 100));
    EXPECT_TRUE(map.contains(10));
    EXPECT_EQ(map.at(10), 100);
}

// updating an existing key should not report a fresh insert
TEST(HashMapTests, InsertSameKeyUpdatesValue) {
    HashMap map(8);
    EXPECT_TRUE(map.insert(5, 50));
    EXPECT_FALSE(map.insert(5, 500));
    EXPECT_TRUE(map.contains(5));
    EXPECT_EQ(map.at(5), 500);
}

// Erase should remove the key
TEST(HashMapTests, EraseRemovesKey) {
    HashMap map(8);
    map.insert(42, 420);
    EXPECT_TRUE(map.contains(42));
    EXPECT_TRUE(map.erase(42));
    EXPECT_FALSE(map.contains(42));
    // erasing again should fail
    EXPECT_FALSE(map.erase(42));
}

// re-insertion path: erase, then insert a new key that should be able to reuse the slot
TEST(HashMapTests, EraseThenInsertNewKeyStillWorks) {
    HashMap map(4);
    map.insert(1, 10);
    map.insert(5, 50);  
    EXPECT_TRUE(map.erase(1));
    EXPECT_TRUE(map.insert(9, 90));
    EXPECT_TRUE(map.contains(9));
    EXPECT_EQ(map.at(9), 90);
}

// throw on missing key
TEST(HashMapTests, AtThrowsOnMissingKey) {
    HashMap map(8);
    map.insert(1, 100);
    EXPECT_THROW(map.at(2), std::out_of_range);
}

// rehash path: push past 0.7 load factor and check all keys still present
TEST(HashMapTests, RehashPreservesEntries) {
    const int N = 200;
    HashMap map(8);  

    for (int i = 0; i < N; ++i) {
        EXPECT_TRUE(map.insert(i, i * 10));
    }

    for (int i = 0; i < N; ++i) {
        EXPECT_TRUE(map.contains(i));
        EXPECT_EQ(map.at(i), i * 10);
    }

    EXPECT_TRUE(map.erase(50));
    EXPECT_FALSE(map.contains(50));
    EXPECT_THROW(map.at(50), std::out_of_range);
}
