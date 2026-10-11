// COMSC-210 | Lab 22 | Edwin Burwell

#include <cstddef>

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

    // Find an item by value and delete it.
    
    void delete_val(int value);
    void delete_pos(size_t position);
    void pop_front();
    void pop_back();

    void print();
    void print_reverse();
};