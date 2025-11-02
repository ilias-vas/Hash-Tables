#include "cuckooTable.hpp"
#include <vector>
#include <algorithm>
#include <tuple>
#include <random>
//https://stackoverflow.com/questions/56655002/generating-a-random-uint64-t
//https://github.com/microsoft/Kuku/tree/main
//https://en.wikipedia.org/wiki/Tabulation_hashing
CuckooTable::CuckooTable(int cap){
    capacity = cap;
    elementsNum = 0;
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
    return residual & (capacity - 1);
}

uint64_t CuckooTable::secondTabulationHash(uint64_t item) {
    uint64_t residual = 0;
    for (int i = 0; i < 8; i++) {
        residual ^= table[i][(char)(item >> 8*i)].second;
    }
    return residual & (capacity - 1);
}

bool CuckooTable::attemptInsert(uint64_t item) { //basically to know if we need to rehash
    if (item == 0) {
        return false; //not having another array to track locations etc means we use 0 as a sentinel
    }

    uint64_t current = item;
    for (int kicks = 0; kicks < maxKicks; kicks++) {
        uint64_t firstHash = firstTabulationHash(current);
        uint64_t secondHash = secondTabulationHash(current);
        if (table1[firstHash] == 0) {
            table1[firstHash] = current;
            elementsNum += 1;
            return true;
        }

        if (table2[secondHash] == 0) {
            table2[secondHash] = current;
            elementsNum += 1;
            return true;
        }

        uint64_t temp = table1[firstHash]; //evicting an element
        table1[firstHash] = current;
        current = temp;
    }
    return false; //max number of kicks
}

void CuckooTable::insert(uint64_t item) {
    if (contains(item)) return;
    if (item == 0) return; //otherwise we loop forever !
    while (!attemptInsert(item)) { //likelihood of this running any more than once is extremely slim
        rehash();
    }
    
}

bool CuckooTable::contains(uint64_t item) {
    if (item == 0) return false;
    uint64_t firstHash = firstTabulationHash(item);
    uint64_t secondHash = secondTabulationHash(item);
    return table1[firstHash] == item || table2[secondHash] == item;
}

bool CuckooTable::remove(uint64_t item) {
    if (item == 0) return false;
    uint64_t firstHash = firstTabulationHash(item);
    uint64_t secondHash = secondTabulationHash(item);

    if (table1[firstHash] == item) {
        table1[firstHash] = 0;
        return true;
    }
    if (table2[secondHash] == item) {
        table2[secondHash] = 0;
        return true;
    }
    return false; 
}

void CuckooTable::rehash() {
    std::vector<uint64_t> vals;
    for (uint64_t val : table1) {
        if (val != 0) {
            vals.push_back(val);
        }
    }
    for (uint64_t val : table2) {
        if (val != 0) {
            vals.push_back(val);
        }
    }

    capacity *= 2;
    std::fill(table1.begin(), table1.end(), 0);
    std::fill(table2.begin(), table2.end(), 0);
    table1.resize(capacity, 0);
    table2.resize(capacity, 0);

    for (uint64_t item : vals) {
        attemptInsert(item);
    }
}

int CuckooTable::getElementCount() {
    return elementsNum;
}

int CuckooTable::getCapacity() {
    return capacity; //capacity of one table
}

