// COMSC-210 | Lab 22 | Edwin Burwell

#include <cstddef>

// The `DoublyLinkedList` class.
//
// Serves as an ordered collection of items.
class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr);
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    // Clears the list.
    void clear();

    // Appends an item to the end of the list.
    //
    // ### Arguments
    //
    // - `value`: The item to append.
    void push_back(int value);

    // Prepends an item to the beginning of the list.
    //
    // ### Arguments
    //
    // - `value`: The item to prepend.
    void push_front(int value);

    // Inserts an item at a given index.
    //
    // ### Arguments
    //
    // - `value`: The item to insert.
    // - `position`: The position to insert at.
    void insert(int value, size_t position);

    // Finds an item by value and delete it.
    //
    // ### Arguments
    //
    // - `value`: The value to compare against while deleting.
    void delete_val(int value);

    // Deletes an item at a given position.
    //
    // ### Arguments
    //
    // - `position`: The position of the item to delete.
    void delete_pos(size_t position);

    // Removes an item from the front of the list.
    void pop_front();

    // Removes an item from the back of the list.
    void pop_back();

    // Displays the contents of the list to `stdout`.
    void print();

    // Displays the contents of the list to `stdout` in reverse order.
    void print_reverse();
};