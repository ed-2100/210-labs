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
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

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
