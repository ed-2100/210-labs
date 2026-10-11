// COMSC-210 | Lab 22 | Edwin Burwell

#include <iostream>
#include <array>
#include <cstdlib>

#include "list.h"

using namespace std;

// The main function.
//
// Demonstrates the `DoublyLinkedList` class various ways.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main() {
    DoublyLinkedList list;
    
    list.print();
    cout << "Calling `push_front(1)`:\n";
    list.push_front(1);
    list.print();

    cout << "\nClearing:\n";
    list.clear();
    list.print();
    
    cout << "\nCalling `push_front(2)`:\n";
    list.clear();
    list.push_front(2);
    list.print();

    cout << "\nCalling `push_front(1)`:\n";
    list.push_front(1);
    list.print();

    cout << "\nCalling `push_back(3)`:\n";
    list.push_back(3);
    list.print();

    cout << "\nCalling `pop_front()`:\n";
    list.pop_front();
    list.print();

    cout << "\nCalling `pop_back()`:\n";
    list.pop_back();
    list.print();

    cout << "\nCalling `pop_front()`:\n";
    list.pop_front();
    list.print();

    cout << "\nCalling `push_back(0)`:\n";
    list.push_back(0);
    list.print();

    cout << "\nCalling `pop_back()`:\n";
    list.pop_back();
    list.print();

    cout << "\nCalling `insert(1, 0)`:\n";
    list.insert(1, 0);
    list.print();

    cout << "\nCalling `insert(0, 0)`:\n";
    list.insert(0, 0);
    list.print();

    cout << "\nCalling `insert(3, 2)`:\n";
    list.insert(3, 2);
    list.print();

    cout << "\nCalling `insert(2, 2)`:\n";
    list.insert(2, 2);
    list.print();

    cout << "\nCalling `delete_pos(2)`:\n";
    list.delete_pos(2);
    list.print();

    cout << "\nCalling `delete_pos(0)`:\n";
    list.delete_pos(0);
    list.print();

    cout << "\nCalling `delete_pos(1)`:\n";
    list.delete_pos(1);
    list.print();

    cout << "\nCalling `delete_pos(0)`:\n";
    list.delete_pos(0);
    list.print();

    cout << "\nFilling the list with `0 1 2 3`:\n";
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(0);
    list.print();

    cout << "\nCalling `print()`:\n";
    list.print();

    cout << "\nCalling `print_reverse()`:\n";
    list.print_reverse();

    cout << "\nCalling `delete_val(2)`:\n";
    list.delete_val(2);
    list.print();

    cout << "\nCalling `delete_val(0)`:\n";
    list.delete_val(0);
    list.print();

    cout << "\nCalling `delete_val(3)`:\n";
    list.delete_val(3);
    list.print();

    cout << "\nCalling `delete_val(1)`:\n";
    list.delete_val(1);
    list.print();

    return EXIT_SUCCESS; // :)
}
