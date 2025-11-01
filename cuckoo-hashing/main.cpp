#include <gtest/gtest.h>
#include "cuckooTable.hpp"
#include <random>
uint64_t generateRandomUInt64_T() {
    std::random_device random;
    std::mt19937_64 generate(random());
    std::uniform_int_distribution<uint64_t> distribution;
    return distribution(generate);
}
std::pair<std::uint64_t, std::uint64_t> table[8][256];
void populateTable() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 256; j++) {
            auto first = generateRandomUInt64_T();
            auto second = generateRandomUInt64_T();
            table[i][j] = std::make_pair(first, second);
        }
    }
}
int firstTabulationHash(uint64_t key) {
    int capacity = 8;
    uint64_t residual = 0;
    for (int i = 0; i < 8; i++) {
        residual ^= table[i][(char)(key >> 8*i)].first;
    }
    return residual & capacity - 1;
}

TEST(hashFunction, hashTesting) {
    auto first = generateRandomUInt64_T();
    auto second = generateRandomUInt64_T();
    populateTable();
    int index = firstTabulationHash(first);
    std::cout << index;

};

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}