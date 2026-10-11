#include <iostream>
#include <array>

#include "list.h"

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Driver program
int main() {
    DoublyLinkedList list;
    
    list.print();
    cout << "Calling `push_front(1)`:\n";
    list.push_front(1);
    list.print();
    
    cout << "\nClearing and calling `push_back(2)`:\n";
    list.clear();
    list.push_back(2);
    list.print();

    cout << "\nCalling `push_front(1)`:\n";
    list.push_front(1);
    list.print();

    cout << "\nCalling `push_back(3)`:\n";
    list.push_back(3);
    list.print();

    cout << "\nCalling `insert(0, 0)`:\n";
    list.insert(0, 0);
    list.print();

    cout << "\nCalling `insert(4, 4)`:\n";
    list.insert(4, 4);
    list.print();

    cout << "\nCalling `pop_front()`:\n";
    list.pop_front();
    list.print();

    cout << "\nCalling `pop_back()`:\n";
    list.pop_back();
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

    cout << "\nCalling `insert(1, 0)\n";
    list.clear();
    list.insert(1, 0);
    list.print();

    cout << "\nCalling `pop_front()`:\n";
    list.pop_front();
    list.print();

    cout << "\nClearing and calling `insert(1, 0)\n";
    list.clear();
    list.insert(1, 0);
    list.print();

    cout << "\nCalling `pop_back()`:\n";
    list.pop_back();
    list.print();

    list.print_reverse();

    list.~DoublyLinkedList();
    list.print();

    return 0;
}
