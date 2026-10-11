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
    Node* newNode = new Node(value);
    if (!tail)  // if there's no tail, the list is empty
        head = tail = newNode;
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoublyLinkedList::push_front(int value) {
    Node* newNode = new Node(value);
    if (!head)  // if there's no head, the list is empty
        head = tail = newNode;
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}
 
void DoublyLinkedList::insert(int value, size_t position) {
    Node* node = new Node(value);

    Node* temp = head;

    if (position == 0) {
        node->next = temp;
        node->prev = nullptr;

        head = node;
        
        if (!temp) {
            tail = node;
        } else {
            temp->prev = node;
        }
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

        temp->next = node;
        
        if (temp->next) {
            temp->next->prev = node;
        } else {
            tail = node;
        }
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

    // Head logic
    head = temp->next;

    // Tail logic
    if (temp->next) {
        temp->next->prev = nullptr;
    } else {
        tail = nullptr;
    }

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