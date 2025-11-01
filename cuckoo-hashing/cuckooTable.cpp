#include "cuckooTable.hpp"
#include <vector>
#include <algorithm>
#include <tuple>
#include <random>
//https://stackoverflow.com/questions/56655002/generating-a-random-uint64-t
//https://github.com/microsoft/Kuku/tree/main
//https://en.wikipedia.org/wiki/Tabulation_hashing
class CuckooTable  {
    private:
        std::pair<std::uint64_t, std::uint64_t> table[8][256];
        std::vector<uint64_t> table1;
        std::vector<uint64_t> table2; //need to assert size at start ?
        int capacity;
        uint64_t generateRandomUInt64_T() {
            std::random_device random;
            std::mt19937_64 generate(random());
            std::uniform_int_distribution<uint64_t> distribution;
            return distribution(generate);
        };
    public: 
        CuckooTable() {
            capacity = 8; //initialize based on this, needs to be power of two
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 256; j++) {
                    auto first = generateRandomUInt64_T();
                    auto second = generateRandomUInt64_T();
                    table[i][j] = std::make_pair(first, second);
            }
        }
        }
        int getCapacity() {
            return capacity;
        }
        int firstTabulationHash(uint64_t key) {
            uint64_t residual = 0;
            for (int i = 0; i < 8; i++) {
                residual ^= table[i][(char)(key >> 8*i)].first;
            }
            return residual & capacity - 1;
        }
        int secondTabulationHash(uint64_t key) {
            uint64_t residual = 0;
            for (int i = 0; i < 8; i++) {
                residual ^= table[i][(char)(key >> 8*i)].second;
            }
            return residual & capacity - 1;
        }
        void insert(int item) {
            //generate locations with first and second hash
            //search table for item
            //kick a bunch of times
            //quit at max kicks
        }

        bool contains(int item) {
            //should be able to hash ? otherwise search whole table
        }

        void rehash() {
            //recreate whole table, move to 2x size or something

        }
};
