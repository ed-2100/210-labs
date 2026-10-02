#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <tuple>
#include <array>

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
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T&;

    ListIterator(Node<T>* current) : current(current) {}

    reference operator*();
    ListIterator<T>& operator++();
    ListIterator<T> operator++(int);
    bool operator==(const ListIterator<T>&) const;
};

string output(List<float>& list);

const int SIZE = 7;

enum MenuState {
    MAIN_MENU,
    MAIN_MENU_DECISION,
    PUSH_FRONT,
    POP_FRONT,
    INSERT,
    REMOVE,
    CLEAR,
    DISPLAY,
    EXIT,
};

const array<tuple<const char*, MenuState>, 7> options = {
    tuple{"Insert", MenuState::INSERT},
    {"Remove", MenuState::REMOVE},
    {"Clear", MenuState::CLEAR},
    {"Display", MenuState::DISPLAY},
    {"Exit", MenuState::EXIT}
};

int main() {
    vector<float> test;

    MenuState state = MAIN_MENU;

    while (true) {
        switch (state) {
            case MAIN_MENU: {
                cout << "Main Menu:\n";

                for (size_t i = 0; i < options.size(); i++) {
                    cout << format("({}) {}\n", i + 1, get<0>(options[i]));
                }

                state = MAIN_MENU_DECISION;
                break;
            }
            case MAIN_MENU_DECISION: {
                cout << "\nYour decision: ";
                
                string buf;

                getline(cin, buf);

                int choice;

                try {
                    choice = stoi(buf);
                } catch (const invalid_argument &e) {
                    cout << "Not a number!";
                    break;
                } catch (const out_of_range &e) {
                    cout << "Definitely out of range.";
                    break;
                }

                if (choice < 1 || choice > options.size()) {
                    cout << "Out of range!";
                    break;
                }

                state = get<1>(options[choice - 1]);

                break;
            }
            case EXIT: {
                cout << "Exiting...\n";
                return EXIT_SUCCESS;
            }
            default:
                // Invalid Menu
                cout << "Menu not found.\n\n";
                state = MenuState::MAIN_MENU;
        }
    }
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
template <typename Data>
void List<T>::insert(Data&& data, size_t idx) {
    if (idx == 0) {
        head = new Node<T> {
            .data = forward<Data>(data),
            .next = head,
        };

        return;
    } else {
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
ListIterator<T> ListIterator<T>::operator++(int) {
    auto tmp = *this;
    ++*this;
    return tmp;
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
