#include <iostream>

#include "list.h"

using namespace std;

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
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

void DoublyLinkedList::insert_after(int value, int position) {
    if (position < 0) {
        cout << "Position must be >= 0." << endl;
        return;
    }

    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
        return;
    }

    Node* temp = head;
    for (int i = 0; i < position && temp; ++i)
        temp = temp->next;

    if (!temp) {
        cout << "Position exceeds list size. Node not inserted.\n";
        delete newNode;
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next)
        temp->next->prev = newNode;
    else
        tail = newNode; // Inserting at the end
    temp->next = newNode;
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

void DoublyLinkedList::delete_pos(size_t pos) {
    Node* temp = head;
    for (size_t i = 0; temp && i < pos; i++) {
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