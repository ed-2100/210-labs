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
    void push_back(int value);
    void push_front(int value);
    void insert(int value, size_t position);
    void delete_val(int value);
    void delete_pos(size_t position);
    void pop_front();
    void pop_back();

    void print();
    void print_reverse();
};