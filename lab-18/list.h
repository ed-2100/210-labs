#pragma once

#include <cstddef>
#include <utility>
#include <algorithm>

namespace mylist {

template <typename T>
class List;

template <typename T>
struct Node;

template <typename T>
class ListIterator;

// The `List` class.
//
// Acts as a container for items.
template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t count;
public:
    List() : head(nullptr), tail(nullptr), count(0) {}
    ~List();

    // Delete the copy constructor and copy assignment
    // operator so that an unintentional shallow copy
    // never happens.
    List(const List<T>& rhs);
    List<T>& operator=(const List<T>& rhs);

    // Explicitly define move semantics.
    List(List<T>&& rhs) noexcept
      : head(std::exchange(rhs.head, nullptr)),
        tail(std::exchange(rhs.tail, nullptr)),
        count(std::exchange(rhs.count, 0)) {}
    List<T>& operator=(List<T>&& other) noexcept;

    // =========================
    // ===== Class Methods =====
    // =========================

    template <typename Item>
    void push_back(Item&& item);

    List<T> clone();

    // Clears the list, freeing all allocations.
    void clear();

    // Returns the current size of the list.
    size_t size() const;

    // =========================
    // ===== Range Methods =====
    // =========================

    ListIterator<T> begin();
    ListIterator<T> end();
};

// The `Node` struct.
//
// The core datatype behind the `List` class.
template <typename T>
struct Node {
    T data;
    Node<T>* next;
};

// The `ListIterator` class.
//
// A simple forward_iterator implementation
// for the `List` class.
template <typename T>
class ListIterator {
private:
    Node<T>* current;
public:
    ListIterator() = default;
    explicit ListIterator(Node<T>* current) : current(current) {}

    T& operator*() const;
    ListIterator<T>& operator++();
    ListIterator<T> operator++(int);
    bool operator==(const ListIterator<T>&) const;
};

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
List<T>::List(const List<T>& rhs)
  : head(nullptr),
    tail(nullptr),
    count(rhs.count) {
    auto front = rhs.begin();
    auto back = rhs.end();
    
    if (front == back) {
        return;
    }

    head = new Node<T> {
        .data = *front,
    };

    tail = head;

    front++;

    for (; front != back; front++) {
        Node<T>* node = new Node<T> {
            .data = *front
        };

        tail->next = node;
        tail = node;
    }

    tail->next = nullptr;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& rhs) {
    if (this != &rhs) {
        this->~List();
        new this List(rhs);
    }
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& rhs) noexcept {
    if (this != &rhs) {
        this->~List();
        new this List(rhs);
    }
    return *this;
}

template <typename T>
template <typename Item>
void List<T>::push_back(Item&& item) {
    Node<T>* node = new Node<T> {
        .data = std::forward<Item>(item),
        .next = nullptr
    };

    if (!tail) {
        head = node;
    } else {
        tail->next = node;
    }

    tail = node;
}

template <typename T>
void List<T>::clear() {
    while (head) {
        Node<T>* current = head;
        head = current->next;
        delete current;
    }

    tail = nullptr;
    count = 0;
}

template <typename T>
size_t List<T>::size() const {
    return count;
}

template <typename T>
ListIterator<T> List<T>::begin() {
    return ListIterator<T>(head);
}

template <typename T>
ListIterator<T> List<T>::end() {
    return ListIterator<T>(nullptr);
}

template <typename T>
T& ListIterator<T>::operator*() const {
    return current->data;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator++() {
    if (current) {
        current = current->next;
    }
    return *this;
}

template <typename T>
ListIterator<T> ListIterator<T>::operator++(int) {
    auto tmp = *this;
    ++*this;
    return tmp;
}

template <typename T>
bool ListIterator<T>::operator==(const ListIterator<T>& rhs) const {
    return current == rhs.current;
}

}; // namespace mylist
