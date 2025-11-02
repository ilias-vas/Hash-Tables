#include <gtest/gtest.h>
#include "cuckooTable.hpp"
#include <random>
#include <unordered_set>

TEST(CuckooTableTests, BasicInsertionAndDeletion) {
    CuckooTable table(8);
    table.insert(42);
    EXPECT_TRUE(table.contains(42));
    EXPECT_FALSE(table.contains(99));
}

TEST(CuckooTableTests, InsertZero) {
    CuckooTable table(8);
    table.insert(0);
    EXPECT_FALSE(table.contains(0));
}

TEST(CuckooTableTests, InsertDuplicate) {
    CuckooTable table(8);
    table.insert(1);
    table.insert(1);
    EXPECT_EQ(1, table.getElementCount());
}

TEST(CuckooTableTests, MultipleInsertions) {
    CuckooTable table(16);
    for (int i = 1; i < 5; i++) {
        table.insert(i);
    }
    for (int i = 1; i < 5; i++) {
        EXPECT_TRUE(table.contains(i));
    }
    EXPECT_FALSE(table.contains(10));
}

TEST(CuckooTableTests, BasicRemove) {
    CuckooTable table(16);
    table.insert(42);

    EXPECT_TRUE(table.contains(42));
    EXPECT_TRUE(table.remove(42));
    EXPECT_FALSE(table.contains(42));
}

TEST(CuckooTableTests, RemoveNonExistent) {
    CuckooTable table(16);
    EXPECT_FALSE(table.remove(42));
}
TEST(CuckooTableTests, RehashOnManyInsertions) {
    CuckooTable table(4);

    for (uint64_t i = 1; i <= 20; i++) {
        table.insert(i);
    }
    for (uint64_t i = 1; i <= 20; i++) {
        EXPECT_TRUE(table.contains(i));
    }
    EXPECT_GT(table.getCapacity(), 4);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}