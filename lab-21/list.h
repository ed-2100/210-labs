#pragma

#include "goat.h"

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

    void push_back(Goat value);
    void push_front(Goat value);
    void insert_after(Goat value, int position);
    void delete_node(Goat value);
    void print();
    void print_reverse();
};