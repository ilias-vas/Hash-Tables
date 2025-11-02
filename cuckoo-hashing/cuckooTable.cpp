#include "cuckooTable.hpp"
#include <vector>
#include <algorithm>
#include <tuple>
#include <random>
//https://stackoverflow.com/questions/56655002/generating-a-random-uint64-t
//https://github.com/microsoft/Kuku/tree/main
//https://en.wikipedia.org/wiki/Tabulation_hashing
CuckooTable::CuckooTable(int capacity) {
    table1.resize(capacity, 0);
    table2.resize(capacity, 0);
    initializeTable();
}

uint64_t CuckooTable::generateRandomUInt64_T() {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    static std::uniform_int_distribution<uint64_t> dist;
    return dist(gen);
}

void CuckooTable::initializeTable() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 256; j++) {
            auto first = generateRandomUInt64_T();
            auto second = generateRandomUInt64_T();
            table[i][j] = std::make_pair(first, second);
        }
    }
}

uint64_t CuckooTable::firstTabulationHash(uint64_t item) {
    uint64_t residual = 0;
    for (int i = 0; i < 8; i++) {
        residual ^= table[i][(char)(item >> 8*i)].first;
    }
    return residual & capacity - 1;
}

uint64_t CuckooTable::secondTabulationHash(uint64_t item) {
    uint64_t residual = 0;
    for (int i = 0; i < 8; i++) {
        residual ^= table[i][(char)(item >> 8*i)].second;
    }
    return residual & capacity - 1;
}

bool CuckooTable::attemptInsert(uint64_t item) { //basically to know if we need to rehash

}

void CuckooTable::insert(uint64_t item) {
    
}

bool CuckooTable::contains(uint64_t item) {

}

bool CuckooTable::remove(uint64_t item) {

}

void CuckooTable::rehash() {
    
}