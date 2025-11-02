#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cstdint>

#include "open-addressing/hashmap.hpp"
#include "cuckoo-hashing/cuckooTable.hpp"

using clock_type = std::chrono::high_resolution_clock;
using ms = std::chrono::duration<double, std::milli>;

struct Result {
    double insert_ms;
    double lookup_ms;
    double erase_ms;
};

Result benchmark_hashmap(std::size_t n, std::uint32_t seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, 1'000'000'000);

    std::vector<int> keys(n);
    for (std::size_t i = 0; i < n; ++i) keys[i] = dist(rng);

    HashMap map(2 * n);

    auto t0 = clock_type::now();
    for (std::size_t i = 0; i < n; ++i)
        map.insert(keys[i], static_cast<int>(i));
    auto t1 = clock_type::now();

    for (std::size_t i = 0; i < n; ++i)
        map.contains(keys[i]);
    auto t2 = clock_type::now();

    for (std::size_t i = 0; i < n; ++i)
        map.erase(keys[i]);
    auto t3 = clock_type::now();

    return { ms(t1 - t0).count(), ms(t2 - t1).count(), ms(t3 - t2).count() };
}

Result benchmark_cuckoo(std::size_t n, std::uint32_t seed) {
    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<std::uint64_t> dist(1, 1'000'000'000ULL);

    std::vector<std::uint64_t> keys(n);
    for (std::size_t i = 0; i < n; ++i) keys[i] = dist(rng);

    CuckooTable table(1 << 15);

    auto t0 = clock_type::now();
    for (std::size_t i = 0; i < n; ++i)
        table.insert(keys[i]);
    auto t1 = clock_type::now();

    for (std::size_t i = 0; i < n; ++i)
        table.contains(keys[i]);
    auto t2 = clock_type::now();

    for (std::size_t i = 0; i < n; ++i)
        table.remove(keys[i]);
    auto t3 = clock_type::now();

    return { ms(t1 - t0).count(), ms(t2 - t1).count(), ms(t3 - t2).count() };
}

int main() {
    const std::size_t N = 100000;
    const std::uint32_t SEED = 42;

    auto hm = benchmark_hashmap(N, SEED);
    auto ck = benchmark_cuckoo(N, SEED);

    std::cout << "=== Open Addressing (linear probing) ===\n";
    std::cout << "insert:\t" << hm.insert_ms << " ms\n";
    std::cout << "lookup:\t" << hm.lookup_ms << " ms\n";
    std::cout << "erase:\t" << hm.erase_ms << " ms\n\n";

    std::cout << "=== Cuckoo Hashing ===\n";
    std::cout << "insert:\t" << ck.insert_ms << " ms\n";
    std::cout << "lookup:\t" << ck.lookup_ms << " ms\n";
    std::cout << "erase:\t" << ck.erase_ms << " ms\n";
}
