# Hash Tables

This repo contains the implementation and tests for two hash-table designs:

- **Cuckoo Hashing** (`cuckoo-hashing/`)
- **Open Addressing with Linear Probing** (`open-addressing/`)

## Build & Run

From the repo root:

### 1. Benchmark both tables

```bash
clang++ -std=c++20 -O2 \
  benchmark_hash_tables.cpp \
  open-addressing/HashMap.cpp \
  cuckoo-hashing/cuckooTable.cpp \
  -o bench

./bench
```
will run on gcc too

### 2. Run open-addressing tests (GoogleTest)
```bash
cd open-addressing
make
./hashmap_tests
```
If your gtest is in a different path, edit the Makefile in open-addressing/ and change the GTEST_INC / GTEST_LIB variables.

### 3. CMake (optional)

There is a CMakeLists.txt in cuckoo-hashing/, so you can also do:

```bash
cd cuckoo-hashing
cmake -S . -B build
cmake --build build
```

This will build the cuckoo target defined there.

---
Authors:
- Ilias Vasiliou
- Craig Jones
