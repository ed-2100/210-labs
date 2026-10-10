#include "list.h"

#include <utility>

using namespace std;

DoublyLinkedList::Node::Node(Goat val, Node* p, Node* n) {
    data = move(val); 
    prev = p;
    next = n;
}

DoublyLinkedList::~DoublyLinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void DoublyLinkedList::push_back(Goat value) {
    Node* newNode = new Node(move(value));
    if (!tail)  // if there's no tail, the list is empty
        head = tail = newNode;
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoublyLinkedList::push_front(Goat value) {
    Node* newNode = new Node(move(value));
    if (!head)  // if there's no head, the list is empty
        head = tail = newNode;
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DoublyLinkedList::insert_after(Goat value, int position) {
    if (position < 0) {
        cout << "Position must be >= 0." << endl;
        return;
    }

    Node* newNode = new Node(move(value));
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

void DoublyLinkedList::delete_node(Goat value) {
    if (!head) return; // Empty list

    Node* temp = head;
    while (temp && temp->data != value)
        temp = temp->next;

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

    delete temp;
}

void DoublyLinkedList::print() {
    Node* current = head;
    if (!current) {
        cout << "List is empty\n";
        return;
    };
    while (current) {
        cout << "    " << current->data << '\n';
        current = current->next;
    }
    cout << endl;
}

void DoublyLinkedList::print_reverse() {
    Node* current = tail;
    if (!current) {
        cout << "List is empty\n";
        return;
    };
    while (current) {
        cout << "    " << current->data << '\n';
        current = current->prev;
    }
    cout << endl;
}
