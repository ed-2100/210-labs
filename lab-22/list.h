#include <cstdint>

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
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    ~DoublyLinkedList();

    void push_back(int value);
    void push_front(int value);
    void insert_after(int value, int position);
    void delete_val(int value);
    int delete_pos(size_t pos);
    int pop_front();
    int pop_back();

    void print();

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};