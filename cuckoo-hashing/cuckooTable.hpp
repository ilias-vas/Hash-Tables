#pragma once
#include <vector>
#include <algorithm>
#include <tuple>
#include <random>
class CuckooTable {
    private:
        std::pair<uint64_t, uint64_t> table[8][256];
        std::vector<uint64_t> table1;
        std::vector<uint64_t> table2;
        int capacity;
        const int maxKicks = 500;
        uint64_t generateRandomUInt64_T();
        void initializeTable();
        bool attemptInsert(uint64_t item);
    public:
        CuckooTable(int capacity = 16);
        void insert(uint64_t item);
        bool contains(uint64_t item);
        bool remove(uint64_t item);
        uint64_t firstTabulationHash(uint64_t item);
        uint64_t secondTabulationHash(uint64_t item);
        void rehash();
        int getCapacity();
        int getSize();
};