#pragma once

#include "goat.h"

// The `DoublyLinkedList` class.
//
// Serves as an ordered collection of items.
class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr);
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList();

    // Appends an item to the end of the list.
    //
    // ### Arguments
    //
    // - `value`: The item to append.
    void push_back(Goat value);

    // Prepends an item to the beginning of the list.
    //
    // ### Arguments
    //
    // - `value`: The item to prepend.
    void push_front(Goat value);

    // Inserts an item after an item at a given index.
    //
    // ### Arguments
    //
    // - `value`: The item to insert.
    // - `position`: The possion of the item to insert after.
    void insert_after(Goat value, int position);

    // Deletes an item matching the item provided.
    //
    // ### Arguments
    //
    // - `value`: The item to compare against while searching.
    void delete_node(Goat value);

    // Displays the contents of the list to `stdout`.
    void print();

    // Displays the contents of the list to `stdout` in reverse order.
    void print_reverse();
};