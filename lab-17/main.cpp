#include <iostream>

using namespace std;

template <typename T>
struct List;

template <typename T>
struct Node;

template <typename T>
struct List {
protected:
    Node<T>* head;
public:
    List() : head(nullptr) {}

    ~List() { // Should be noexcept later on...
        throw logic_error("Unimplmented!");
    }

    template <typename Data>
    void push_front(Data&& data);

    T pop_front();

    template <typename Data>
    void insert(Data&& data, size_t idx);

    T remove(size_t idx);

    string to_string() const;
};

template <typename T>
struct Node {
    T data;
    Node<T> *next;
};

template <typename T>
template <typename Data>
void List<T>::push_front(Data&& data) {
    Node<T>* node = new Node<T> {
        .data = forward<Data>(data);
        .next = head;
    }

    head = node;
}

template <typename T>
T List<T>::pop_front() {
    Node<T>* current = head;

    head = current->next;

    T data = move(current->data);

    delete current;

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
        .data = forward<Data>(data);
        .next = current->next;
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

    
}

// string List::to_string() const {}

// const int SIZE = 7;

// void output(Node *);

int main() {
    // Node *head = nullptr;
    // int count = 0;

    // // create a linked list of size SIZE with random numbers 0-99
    // for (int i = 0; i < SIZE; i++) {
    //     int tmp_val = rand() % 100;
    //     Node *newVal = new Node;

    //     // adds node at head
    //     if (!head) {
    //         head = newVal;
    //         newVal->next = nullptr;
    //         newVal->value = tmp_val;
    //     }
    //     else {
    //         newVal->next = head;
    //         newVal->value = tmp_val;
    //         head = newVal;
    //     }
    // }
    // output(head);

    // // deleting a node
    // cout << "Which node to delete? " << endl;
    // output(head);
    // int entry;
    // cout << "Choice --> ";
    // cin >> entry;

    // // traverse that many times and delete that node
    // Node *current = head;
    // Node *prev = nullptr;  // start prev as nullptr to detect head deletion

    // for (int i = 0; i < (entry - 1); i++) {
    //     prev = current;
    //     current = current->next;
    // }

    // // at this point, delete current and reroute pointers
    // if (current) {
    //     if (prev == nullptr) {
    //         // deleting the head node
    //         head = current->next;
    //     } else {
    //         prev->next = current->next;
    //     }
    //     delete current;
    //     current = nullptr;
    // }
    // output(head);

    // // insert a node
    // cout << "After which node to insert 10000? " << endl;
    // count = 1;
    // current = head;
    // while (current) {
    //     cout << "[" << count++ << "] " << current->value << endl;
    //     current = current->next;
    // }
    // cout << "Choice --> ";
    // cin >> entry;

    // current = head;
    // prev = nullptr;  // reset prev to nullptr for same reason

    // for (int i = 0; i < entry; i++) {
    //     prev = current;
    //     current = current->next;
    // }

    // // at this point, insert a node between prev and current
    // Node *newnode = new Node;
    // newnode->value = 10000;
    // newnode->next = current;

    // if (prev == nullptr) {
    //     // inserting before the head
    //     head = newnode;
    // } else {
    //     prev->next = newnode;
    // }
    // output(head);

    // // deleting the linked list
    // current = head;
    // while (current) {
    //     head = current->next;
    //     delete current;
    //     current = head;
    // }
    // head = nullptr;
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
