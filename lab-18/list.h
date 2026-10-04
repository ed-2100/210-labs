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
    size_t count;
public:
    List() : count(0), head(nullptr) {}
    ~List();

    // Delete the copy constructor and copy assignment
    // operator so that an unintentional shallow copy
    // never happens.
    List(const List<T>& rhs) = delete;
    List<T>& operator=(const List<T>&) = delete;

    // Explicitly define move semantics.
    List(List<T>&& rhs) noexcept
      : head(std::exchange(rhs.head, nullptr)),
        count(std::exchange(rhs.count, 0)) {}
    List<T>& operator=(List<T>&& other) noexcept;

    // =========================
    // ===== Class Methods =====
    // =========================

    // Inserts a value at an arbitrary index.
    //
    // ### Arguments
    //
    //  - `data`: The data to insert.
    //  - `idx`: The index to insert the data at.
    template <typename Data>
    void insert(Data&& data, size_t idx);

    // Removes a value at an arbitrary index.
    //
    // ### Arguments
    //
    //  - `idx`: The index to remove.
    //
    // ### Returns
    //
    // The data contained at the removed index.
    T remove(size_t idx);

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
List<T>& List<T>::operator=(List<T>&& other) noexcept {
    if (this != &other) {
        this->~List();

        head = std::exchange(other.head, nullptr);
        count = std::exchange(other.count, 0);
    }
    return *this;
}

template <typename T>
template <typename Data>
void List<T>::insert(Data&& data, size_t idx) {
    Node<T>* node = new Node<T> {
        .data = std::forward<Data>(data),
    };
    
    if (idx == 0) {
        node->next = head;
        head = node;
    } else {
        Node<T>* current = head;

        for (size_t i = 1; i < idx; i++) {
            current = current->next;
        }

        node->next = current->next;
        current->next = node;
    }

    count += 1;
}

template <typename T>
T List<T>::remove(size_t idx) {
    Node<T>* removed;

    if (idx == 0) {
        removed = head;
        head = removed->next;
    } else {
        Node<T>* current = head;

        for (size_t i = 1; i < idx; i++) {
            current = current->next;
        }

        removed = current->next;
        current->next = removed->next;
    }
    
    T data = std::move(removed->data);

    delete removed;

    count -= 1;

    return std::move(data);
}

template <typename T>
void List<T>::clear() {
    while (head) {
        Node<T>* current = head;
        head = current->next;
        delete current;
    }

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
