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

int DoublyLinkedList::delete_val(int value) {
    if (!head) return; // Empty list

    Node* temp = head;
    while (temp && temp->data != value) {
        temp = temp->next;
    }

    if (!temp) return; // Value not found

    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next; // Deleting the head
    }

    if (temp->next) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev; // Deleting the tail
    }

    int data = move(temp->data);

    delete temp;

    return move(data);
}

int DoublyLinkedList::delete_pos(size_t pos) {
    if (!head) return; // Empty list

    Node* temp = head;
    for (size_t i = 0; temp && i < pos; i++) {
        temp = temp->next;
    }

    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next; // Deleting the head
    }

    if (temp->next) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev; // Deleting the tail
    }

    int data = move(temp->data);

    delete temp;

    return move(data);
}

int DoublyLinkedList::pop_front() {
    if (!head) return;

    Node* temp = head;

    head = temp->next;

    if (temp->next) {
        temp->next->prev = nullptr;
    } else {
        tail = nullptr;
    }

    int data = move(temp->data);

    delete temp;

    return move(data);
}

int DoublyLinkedList::pop_back() {
    if (!tail) return;

    Node* temp = tail;

    if (temp->prev) {
        temp->prev->next = nullptr;
    } else {
        head = nullptr;
    }

    tail = temp->prev;

    int data = move(temp->data);

    delete temp;

    return move(data);
}

void DoublyLinkedList::print() {
    Node* current = head;
    if (!current) return;
    cout << "List forward: ";
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void DoublyLinkedList::print_reverse() {
    Node* current = tail;
    cout << "List backward: ";
    if (!current) return;
    while (current) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}