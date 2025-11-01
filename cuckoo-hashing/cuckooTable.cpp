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
        uint64_t generateRandomUInt64_T() {
            std::random_device random;
            std::mt19937_64 generate(random());
            std::uniform_int_distribution<uint64_t> distribution;
            return distribution(generate);
        };
    public: 
        CuckooTable() {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 256; j++) {
                    auto first = generateRandomUInt64_T();
                    auto second = generateRandomUInt64_T();
                    table[i][j] = std::make_pair(first, second);
            }
        }
        }
        uint64_t firstTabulationHash(uint64_t key) {
            uint64_t residual = 0;
            for (int i = 0; i < 8; i++) {
                residual ^= table[i][(char)(key >> 8*i)].first;
            }
            return residual;
        }
        uint64_t secondTabulationHash(uint64_t key) {
            uint64_t residual = 0;
            for (int i = 0; i < 8; i++) {
                residual ^= table[i][(char)(key >> 8*i)].second;
            }
            return residual;
        }
        void insert(int item) {
            std::ignore = item;
        }

        bool contains(int item) {
            return true;
        }

        void rehash() {
            //
        }
};
