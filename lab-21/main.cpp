#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <utility>
#include <format>

#include "list.h"

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Driver program
int main() {
    DoublyLinkedList list;

    auto current_time = chrono::steady_clock::now();
    mt19937 gen(current_time.time_since_epoch().count());
    uniform_int_distribution<uint32_t> dist_size(MIN_LS, MAX_LS);

    int size = dist_size(gen);

    for (int i = 0; i < size; ++i)
        list.push_back(move(Goat()));
    cout << "List forward:\n";
    list.print();

    cout << "List backward:\n";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward:\n";
    list.print();

    return 0;
}
