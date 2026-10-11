#include <cstddef>

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void push_back(int value);
    void push_front(int value);
    void insert_after(int value, int position);
    void delete_val(int value);
    void delete_pos(size_t pos);
    void pop_front();
    void pop_back();

    void print();
    void print_reverse();
};