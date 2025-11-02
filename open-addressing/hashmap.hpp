#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <vector>
#include <cstddef>

class HashMap {
public:
    explicit HashMap(std::size_t initial_capacity = 8);

    bool insert(int key, int value);
    bool erase(int key);
    bool contains(int key) const;

    int& at(int key);
    const int& at(int key) const;

private:
    enum class State { EMPTY, OCCUPIED, DELETED };

    struct Slot {
        int key;
        int value;
        State state;
    };

    std::vector<Slot> table;
    std::size_t count;
    std::size_t tombstones;

    void init_table(std::size_t n);
    double load_factor() const;
    std::size_t hash_key(int key) const;
    bool find_slot(int key, std::size_t& out_idx) const;
    bool insert_internal(int key, int value);
    void rehash(std::size_t new_cap);
};

#endif
