#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <tuple>
#include <array>

#include "list.h"

using namespace std;
using namespace mylist;

enum MenuState {
    MAIN_MENU,
    MAIN_MENU_DECISION,
    INSERT,
    REMOVE,
    CLEAR,
    DISPLAY,
    EXIT,
};

class Application {
private:
    List<float> list;
    MenuState state = MAIN_MENU;

public:
    int run();

private:
    // The `main_menu` state function.
    //
    // Displays a list of list operations.
    void main_menu();

    // The `main_menu_decision` state function.
    //
    // Selects the state based on user input.
    void main_menu_decision();

    // The `insert` state function.
    //
    // Inserts a node at a position in the list
    // based on user input.
    void insert();

    // The `remove` state function.
    //
    // Removes a node at a position in the list
    // based on user input.
    void remove();

    // The `clear` state function.
    //
    // Clears the list and returns to the main
    // menu.
    void clear();

    // The `display` state function.
    //
    // Displays the current contents of the list.
    void display();
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

int main() {
    Application app;

    return app.run();
}

int Application::run() {
    list = List<float>();
    state = MAIN_MENU;

    while (true) {
        switch (state) {
            case MAIN_MENU:
                main_menu();
                break;
            case MAIN_MENU_DECISION:
                main_menu_decision();
                break;
            case INSERT:
                insert();
                break;
            case REMOVE:
                remove();
                break;
            case CLEAR:
                clear();
                break;
            case DISPLAY:
                display();
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

void Application::main_menu() {
    cout << "Main Menu:\n";

    for (size_t i = 0; i < options.size(); i++) {
        cout << format("({}) {}\n", i + 1, get<0>(options[i]));
    }

    state = MAIN_MENU_DECISION;
}

void Application::main_menu_decision() {
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

void Application::insert() {
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

void Application::remove()  {
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

void Application::clear() {
    cout << "Clearing list...";

    list.clear();

    cout << " Cleared.\n";

    state = MAIN_MENU;
}

void Application::display() {
    cout << "Current list contents:\n";
    
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

    buf.append_range(" ]\n");

    return buf;

    state = MAIN_MENU;
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
