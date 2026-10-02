#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <tuple>
#include <array>

#include "List.h"

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
    size_t count;
public:
    List() : count(0), head(nullptr) {}
    ~List();

    template <typename Data>
    void insert(Data&& data, size_t idx);

    T remove(size_t idx);

    ListIterator<T> begin();
    ListIterator<T> end();

    void clear();

    size_t size() const;
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

enum MenuState {
    MAIN_MENU,
    MAIN_MENU_DECISION,
    INSERT,
    REMOVE,
    CLEAR,
    DISPLAY,
    EXIT,
};

const array<tuple<const char*, MenuState>, 5> options = {
    tuple{"Insert", MenuState::INSERT},
    {"Remove", MenuState::REMOVE},
    {"Clear", MenuState::CLEAR},
    {"Display", MenuState::DISPLAY},
    {"Exit", MenuState::EXIT}
};

string output(List<float>& list);
bool parse_int(int& num, const string& input);

void state_main_menu(MenuState& state, List<float>& list);
void state_main_menu_decision(MenuState& state, List<float>& list);
void state_insert(MenuState& state, List<float>& list);
void state_remove(MenuState& state, List<float>& list);
void state_clear(MenuState& state, List<float>& list);
void state_display(MenuState& state, List<float>& list);

int main() {
    List<float> list;
    MenuState state = MAIN_MENU;

    while (true) {
        switch (state) {
            case MAIN_MENU:
                state_main_menu(state, list);
                break;
            case MAIN_MENU_DECISION:
                state_main_menu_decision(state, list);
                break;
            case INSERT:
                state_insert(state, list);
                break;
            case REMOVE:
                state_remove(state, list);
                break;
            case CLEAR:
                state_clear(state, list);
                break;
            case DISPLAY:
                state_display(state, list);
                break;
            case EXIT:
                cout << "Exiting...\n";
                return EXIT_SUCCESS;
            default:
                // Invalid Menu
                cout << "Menu not found.\n";
                state = MenuState::MAIN_MENU;
        }

        cout << '\n';
    }
}

bool parse_int(int& num, const string& input) {
    try {
        num = stoi(input);
    } catch (const invalid_argument &e) {
        cout << "Not a number!\n";
        return false;
    } catch (const out_of_range &e) {
        cout << "Definitely out of range.\n";
        return false;
    }

    return true;
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
template <typename Data>
void List<T>::insert(Data&& data, size_t idx) {
    Node<T>* node = new Node<T> {
        .data = forward<Data>(data),
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
    
    T data = move(removed->data);

    delete removed;

    count -= 1;

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

    count = 0;
}

template <typename T>
size_t List<T>::size() const {
    return count;
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

void state_main_menu(MenuState& state, List<float>& list) {
    cout << "Main Menu:\n";

    for (size_t i = 0; i < options.size(); i++) {
        cout << format("({}) {}\n", i + 1, get<0>(options[i]));
    }

    state = MAIN_MENU_DECISION;
}

void state_main_menu_decision(MenuState& state, List<float>& list) {
    cout << "Your decision: ";
    
    string buf;
    getline(cin, buf);

    int choice;
    if (!parse_int(choice, buf)) {
        return;
    }

    if (choice < 1 || choice > options.size()) {
        cout << "Out of range!\n";
        return;
    }

    state = get<1>(options[choice - 1]);
}

void state_insert(MenuState& state, List<float>& list){
    cout << "Index to insert at: ";

    string buf;
    getline(cin, buf);

    int index;
    if (!parse_int(index, buf)) {
        state = MAIN_MENU;
        return;
    }

    if (index < 0 || index > list.size()) {
        cout << "Out of range!\n";
        state = MAIN_MENU;
        return;
    }

    cout << "Value to insert (float): ";

    getline(cin, buf);

    float number;
    try {
        number = stof(buf);
    } catch (const invalid_argument &e) {
        cout << "Not a number!\n";
        state = MAIN_MENU;
        return;
    } catch (const out_of_range &e) {
        cout << "floats cannot represent that large of a number.\n";
        state = MAIN_MENU;
        return;
    }

    list.insert(number, index);
    
    cout << format("\nInserted value: {}\n", number);

    state = MAIN_MENU;
}

void state_remove(MenuState& state, List<float>& list)  {
    if (list.size() == 0) {
        cout << "No elements to remove.\n";
        state = MAIN_MENU;
        return;
    }

    cout << "Index to remove: ";

    string buf;
    getline(cin, buf);

    int choice;
    if (!parse_int(choice, buf)) {
        state = MAIN_MENU;
        return;
    }

    if (choice < 0 || choice >= list.size()) {
        cout << "Out of range!\n";
        state = MAIN_MENU;
        return;
    }

    cout << format("\nRemoved value: {}\n", list.remove(choice));

    state = MAIN_MENU;
}

void state_clear(MenuState& state, List<float>& list) {
    cout << "Clearing list...";

    list.clear();

    cout << " Cleared.\n";

    state = MAIN_MENU;
}

void state_display(MenuState& state, List<float>& list) {
    cout << "Current list contents:\n"
         << output(list) << '\n';

    state = MAIN_MENU;
}
