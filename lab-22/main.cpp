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
    list.~DoublyLinkedList();
    list.push_back(2);
    list.print();
    cout << "\nCalling `push_front(1)`:\n";
    list.push_front(1);
    list.print();

    list.print_reverse();

    list.~DoublyLinkedList();
    list.print();

    return 0;
}
