#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <tuple>
#include <array>

#include "list.h"

using namespace std;
using namespace list;

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
    List<float>& list;
    MenuState state = MAIN_MENU;

public:
    int run();

private:
    void main_menu();
    void main_menu_decision();
    void insert();
    void remove();
    void clear();
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
    List<float> list;

    List<float> list1 = list;
    List<float> list2 = list;

    // Application app;

    // return app.run();
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

void Astate_insert(MenuState& state, List<float>& list){
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
