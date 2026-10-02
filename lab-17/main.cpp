#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template <typename T>
struct List;

template <typename T>
struct Node;

template <typename T>
struct ListIterator;

template <typename T>
struct List {
private:
    Node<T>* head;
    Node<T>* tail; // TODO: Update this in the functions.
public:
    List() : head(nullptr) {}
    ~List();

    template <typename Data>
    void push_front(Data&& data);

    T pop_front();

    template <typename Data>
    void insert(Data&& data, size_t idx);

    T remove(size_t idx);

    ListIterator<T> begin();
    ListIterator<T> end();

    void clear();
};

template <typename T>
struct Node {
    T data;
    Node<T>* next;
};

template <typename T>
struct ListIterator {
private:
    Node<T>* current;
public:
    using difference_type = std::ptrdiff_t; // Not sure if I need to change this yet.
    using value_type = T;
    using reference = T&;

    ListIterator(Node<T>* current) : current(current) {}

    reference operator*();

    ListIterator<T>& operator++();

    ListIterator<T> operator++(int) {
        auto tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const ListIterator<T>&) const;
};

string float_list_to_string();

const int SIZE = 7;

// void output(Node *);

int main() {
    vector<float> test;

    // create a linked list of size SIZE with random numbers 0-99
    List<float> list;

    for (int i = 0; i < SIZE; i++) {
        list.push_front(float(rand() % 100));
    }

    // output(head);

    // deleting a node
    cout << "Which node to delete?" << endl;
    // output(head);
    int entry;
    cout << "Choice --> ";
    cin >> entry;

    // traverse that many times and delete that node
    list.remove(entry);
    // output(head);

    // insert a node
    cout << "After which node to insert 10000? " << endl;
    // output(head);
    cout << "Choice --> ";
    cin >> entry;

    list.insert(10000.0f, entry);
    // output(head);

    // deleting the linked list
    list.clear();
    // output(head);

    return EXIT_SUCCESS;
}

// void output(Node *hd) {
//     if (!hd) {
//         cout << "Empty list.\n";
//         return;
//     }
//     int count = 1;
//     Node *current = hd;
//     while (current) {
//         cout << "[" << count++ << "] " << current->value << endl;
//         current = current->next;
//     }
//     cout << endl;
// }

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
template <typename Data>
void List<T>::push_front(Data&& data) {
    Node<T>* node = new Node<T> {
        .data = forward<Data>(data),
        .next = head,
    };

    head = node;
}

template <typename T>
T List<T>::pop_front() {
    Node<T>* popped = head;

    head = popped->next;

    T data = move(popped->data);

    delete popped;

    return move(data);
}

template <typename T>
template <typename Data>
void List<T>::insert(Data&& data, size_t idx) {
    if (idx == 0) {
        push_front(forward<Data>(data));
        return;
    }

    Node<T>* current = head;

    for (size_t i = 1; i < idx; i++) {
        current = current->next;
    }

    Node<T>* node = new Node<T> {
        .data = forward<Data>(data),
        .next = current->next,
    };

    current->next = node;
}

template <typename T>
T List<T>::remove(size_t idx) {
    if (idx == 0) {
        return pop_front();
    }

    Node<T>* current = head;

    for (size_t i = 1; i < idx; i++) {
        current = current->next;
    }

    Node<T>* removed = current->next;

    current->next = removed->next;

    T data = move(removed->data);

    delete removed;

    return move(data);
}

template <typename T>
ListIterator<T> List<T>::begin() {
    return ListIterator<T>(head);
}

template <typename T>
ListIterator<T> List<T>::end() {
    return ListIterator<T>(tail);
}

template <typename T>
void List<T>::clear() {
    while (head) {
        Node<T>* current = head;
        head = current->next;
        delete current;
    }
}

template <typename T>
ListIterator<T>::reference ListIterator<T>::operator*() {
    return current->data;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator++() {
    current = current->next;
    return *this;
}

template <typename T>
bool ListIterator<T>::operator==(const ListIterator<T>& rhs) const {
    return current == rhs.current;
}

string float_list_to_string() {}
