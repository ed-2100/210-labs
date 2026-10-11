#include <iostream>

#include "list.h"

using namespace std;

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

void DoublyLinkedList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
}

void DoublyLinkedList::push_back(int value) {
    Node* node = new Node(value);

    // Head logic
    if (tail) {
        node->prev = tail;
        tail->next = node;
    } else {
        head = node;
    }

    // Tail logic
    tail = node;
}

void DoublyLinkedList::push_front(int value) {
    Node* node = new Node(value);

    // Tail logic
    if (head) {
        node->next = head;
        head->prev = node;
    } else {
        tail = node;
    }

    // Head logic
    head = node;
}
 
void DoublyLinkedList::insert(int value, size_t position) {
    Node* node = new Node(value);

    Node* temp = head;

    if (position == 0) {
        node->next = temp;
        node->prev = nullptr;
        
        // Tail logic
        if (temp) {
            temp->prev = node;
        } else {
            tail = node;
        }

        // Head logic
        head = node;
    } else {
        for (size_t i = 1; temp && i < position; i++) {
            temp = temp->next;
        }

        if (!temp) {
            delete node;
            return;
        }

        node->next = temp->next;
        node->prev = temp;
        
        // Tail logic
        if (temp->next) {
            temp->next->prev = node;
        } else {
            tail = node;
        }

        // Head logic
        temp->next = node;
    }
}

void DoublyLinkedList::delete_val(int value) {
    Node* temp = head;
    while (temp && temp->data != value) {
        temp = temp->next;
    }

    if (!temp) return;

    // Head logic
    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    // Tail logic
    if (temp->next) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;
    }

    delete temp;
}

void DoublyLinkedList::delete_pos(size_t position) {
    Node* temp = head;
    for (size_t i = 0; temp && i < position; i++) {
        temp = temp->next;
    }

    if (!temp) return;

    // Head logic
    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    // Tail logic
    if (temp->next) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;
    }

    delete temp;
}

void DoublyLinkedList::pop_front() {
    Node* temp = head;

    if (!temp) return;

    // Tail logic
    if (temp->next) {
        temp->next->prev = nullptr;
    } else {
        tail = nullptr;
    }

    // Head logic
    head = temp->next;

    delete temp;
}

void DoublyLinkedList::pop_back() {
    Node* temp = tail;

    if (!temp) return;

    // Head logic
    if (temp->prev) {
        temp->prev->next = nullptr;
    } else {
        head = nullptr;
    }

    // Tail logic
    tail = temp->prev;

    delete temp;
}

void DoublyLinkedList::print() {
    Node* current = head;
    cout << "List forward:";
    while (current) {
        cout << ' ' << current->data;
        current = current->next;
    }
    cout << endl;
}

void DoublyLinkedList::print_reverse() {
    Node* current = tail;
    cout << "List backward:";
    while (current) {
        cout << ' ' << current->data;
        current = current->prev;
    }
    cout << endl;
}