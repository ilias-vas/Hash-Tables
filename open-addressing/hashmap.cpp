#include "hashmap.hpp"
#include <functional>
#include <stdexcept>

HashMap::HashMap(std::size_t initial_capacity)
    : count(0), tombstones(0) {
    init_table(initial_capacity);
}

bool HashMap::insert(int key, int value) {
    if (load_factor() > 0.7)
        rehash(table.size() * 2);
    return insert_internal(key, value);
}

bool HashMap::erase(int key) {
    std::size_t idx;
    if (!find_slot(key, idx)) return false;
    table[idx].state = State::DELETED;
    --count;
    ++tombstones;
    return true;
}

bool HashMap::contains(int key) const {
    std::size_t idx;
    return find_slot(key, idx);
}

int& HashMap::at(int key) {
    std::size_t idx;
    if (!find_slot(key, idx))
        throw std::out_of_range("key not found");
    return table[idx].value;
}

const int& HashMap::at(int key) const {
    std::size_t idx;
    if (!find_slot(key, idx))
        throw std::out_of_range("key not found");
    return table[idx].value;
}

void HashMap::init_table(std::size_t n) {
    table.clear();
    table.resize(n);
    count = 0;
    tombstones = 0;
}

double HashMap::load_factor() const {
    return static_cast<double>(count + tombstones) / table.size();
}

std::size_t HashMap::hash_key(int key) const {
    return std::hash<int>{}(key) % table.size();
}

bool HashMap::find_slot(int key, std::size_t& out_idx) const {
    std::size_t idx = hash_key(key);
    std::size_t start = idx;
    while (true) {
        const auto& slot = table[idx];
        if (slot.state == State::EMPTY) {
            return false;
        }
        if (slot.state == State::OCCUPIED && slot.key == key) {
            out_idx = idx;
            return true;
        }
        idx = (idx + 1) % table.size();
        if (idx == start) return false;
    }
}

bool HashMap::insert_internal(int key, int value) {
    std::size_t idx = hash_key(key);
    std::size_t first_tombstone = table.size();

    while (true) {
        auto& slot = table[idx];
        if (slot.state == State::EMPTY) {
            std::size_t target = (first_tombstone != table.size()) ? first_tombstone : idx;
            table[target].key = key;
            table[target].value = value;
            if (first_tombstone != table.size()) {
                table[target].state = State::OCCUPIED;
                --tombstones;
            } else {
                table[target].state = State::OCCUPIED;
            }
            ++count;
            return true;
        } else if (slot.state == State::DELETED) {
            if (first_tombstone == table.size())
                first_tombstone = idx;
        } else if (slot.state == State::OCCUPIED && slot.key == key) {
            slot.value = value;   // update
            return false;
        }
        idx = (idx + 1) % table.size();
    }
}

void HashMap::rehash(std::size_t new_cap) {
    std::vector<Slot> old = std::move(table);
    init_table(new_cap);
    for (auto& slot : old) {
        if (slot.state == State::OCCUPIED) {
            insert_internal(slot.key, slot.value);
        }
    }
}
