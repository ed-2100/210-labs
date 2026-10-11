// COMSC-210 | Lab 21 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <utility>
#include <format>

#include "list.h"

using namespace std;

// The main function.
//
// Prints random lists of goats in various orderings.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main() {
    DoublyLinkedList list;

    auto current_time = chrono::steady_clock::now();
    mt19937 gen(current_time.time_since_epoch().count());
    uniform_int_distribution<uint32_t> dist_size(5, 20);

    int size = dist_size(gen);

    for (int i = 0; i < size; ++i) {
        list.push_back(move(Goat()));
    }

    list.print();
    cout << '\n';

    list.print_reverse();
    cout << '\n';

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    list.print();

    return 0;
}
