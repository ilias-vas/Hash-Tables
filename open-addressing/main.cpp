#include <iostream>
#include "hashmap.hpp"

int main() {
    HashMap hm(4);

    // insert some values
    hm.insert(10, 100);
    hm.insert(14, 140);
    hm.insert(18, 180);

    std::cout << "Contains 10: " << hm.contains(10) << "\n";
    std::cout << "Contains 14: " << hm.contains(14) << "\n";
    std::cout << "Contains 18: " << hm.contains(18) << "\n";
    std::cout << "Contains 99: " << hm.contains(99) << "\n";

    // read them
    std::cout << "10 -> " << hm.at(10) << "\n";
    std::cout << "14 -> " << hm.at(14) << "\n";
    std::cout << "18 -> " << hm.at(18) << "\n";

    // overwrite existing key
    hm.insert(14, 999);
    std::cout << "14 (after overwrite) -> " << hm.at(14) << "\n";

    // erase one
    hm.erase(14);
    std::cout << "Contains 14: " << hm.contains(14) << "\n";

    // re-insert after a deletion (tests tombstone logic)
    hm.insert(14, 1400);
    std::cout << "14 (after reinsert): " << hm.at(14) << "\n";

    // try missing key safely
    try {
        std::cout << "99: " << hm.at(99) << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "lookup of 99 failed: " << e.what() << "\n";
    }

    return 0;
}
