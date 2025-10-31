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
        uint64_t generateRandomUInt64_T() {
            std::random_device random;
            std::mt19937_64 generate(random());
            std::uniform_int_distribution<uint64_t> distribution;
            return distribution(generate);
        };
        std::vector<std::vector<uint64_t>> populateTable(std::vector<std::vector<std::uint64_t>> table) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 256; j++) {
                table[i][j] = generateRandomUInt64_T();
            }
        }
        return table;
        }

    public: 
        void insert(int item) {
            std::ignore = item;
        }

        bool contains(int item) {
            return true;
        }

        void tabulationHash(int item) {
            std::ignore = item;
        }
};
