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

string output(List<float>& list);

const int SIZE = 7;

int main() {
    vector<float> test;

    // create a linked list of size SIZE with random numbers 0-99
    List<float> list;

    for (int i = 0; i < SIZE; i++) {
        list.push_front(float(rand() % 100));
    }

    cout << output(list) << endl;

    // deleting a node
    cout << "Which node to delete?" << endl;
    cout << output(list) << endl;
    int entry;
    cout << "Choice --> ";
    cin >> entry;

    // traverse that many times and delete that node
    list.remove(entry);
    cout << output(list) << endl;

    // insert a node
    cout << "After which node to insert 10000? " << endl;
    cout << output(list) << endl;
    cout << "Choice --> ";
    cin >> entry;

    list.insert(10000.0f, entry);
    cout << output(list) << endl;

    // deleting the linked list
    list.clear();
    cout << output(list) << endl;

    return EXIT_SUCCESS;
}

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
    return ListIterator<T>(nullptr);
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

string output(List<float>& list) {
    auto front = list.begin();
    auto back = list.end();

    string buf;

    buf.append_range("[ ");

    if (front == back) {
        buf.append_range("]");
        return move(buf);
    }

    while (true) {
        buf.append_range(format("{}", *front));

        front++;

        if (front == back) {
            break;
        }

        buf.append_range(", ");
    }

    buf.append_range(" ]");

    return buf;
}
