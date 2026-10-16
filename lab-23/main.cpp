// COMSC-210 | Lab 17 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.
//
// I'm documenting my modularization choices here, because it doesn't really
// fit well anywhere in the rest of the codebase.
//
// Initially, I started by modularizing the list implementation into a class,
// because it would allow me to create a unified user-facing API. I decided
// to write an iterator implementation, because I thought it would simplify
// my for loops. In the end, I didn't end up using a for loop, but the
// iterator came in handy in the `display` function anyway. It allowed me to
// leave all member variables of `List` private, while still getting keeping
// all the display logic outside of the `List` code. After modularizing the
// list function, I went about writing the menu. I decided on a state machine
// architecture, because it would allow me to expand it if it turned out that
// I needed to, which I did. After a while, I realized that my main function
// was becoming far too big and the switch statement was already well over
// past best-practice cognitive complexity standards. That's when I decided
// to make the `Application` class. It allowed me to pull the rest of the
// goofiness out of `main` and properly modularize it.

#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <tuple>
#include <array>
#include <list>

using namespace std;

// The `MenuState` enum.
//
// Describes the different states in 
// the `Application` class's internal
// state machine.
enum MenuState {
    MAIN_MENU,
    MAIN_MENU_DECISION,
    APPEND,
    REMOVE,
    DISPLAY,
    EXIT,
};

// The `Application` class.
//
// Encloses the state-machine logic into a
// unified structure for this assignment.
class Application {
private:
    list<float> listy;
    MenuState state = MAIN_MENU;

public:
    // The `run` function.
    //
    // Runs the `Application`.
    //
    // ### Returns:
    //
    // A signed integer value, where `0` means success.
    int run();

private:
    // The `main_menu` state function.
    //
    // Displays a list of list operations to the user.
    // and sets `state` to `MAIN_MENU_DECISION`.
    void main_menu();

    // The `main_menu_decision` state function.
    //
    // Selects the state based on user input.
    void main_menu_decision();

    // The `append` state function.
    //
    // Appends a node to the list.
    void append();

    // The `remove` state function.
    //
    // Removes a node at a position in the list
    // based on user input.
    void remove();

    // The `display` state function.
    //
    // Displays the current contents of the list.
    void display();

    // A small helper to parse integer inputs.
    //
    // ### Arguments
    //
    //  - `num`: Location to store the integer.
    //  - `input`: The input string to parse.
    //
    // ### Returns
    //
    // A bool, where true means the parse was
    // successful.
    static bool parse_int(
        int& num,
        const string& input
    );
};

// The `main` function.
//
// Showcases a minimal list implementation, allowing
// the user to perform arbitrary operations to test
// its functionality.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main() {
    Application app;

    return app.run(); // :)
}

int Application::run() {
    listy = list<float>();
    state = MAIN_MENU;

    while (true) {
        switch (state) {
            case MAIN_MENU:
                main_menu();
                break;
            case MAIN_MENU_DECISION:
                main_menu_decision();
                break;
            case APPEND:
                append();
                break;
            case REMOVE:
                remove();
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

const array<tuple<const char*, MenuState>, 5> options = {
    tuple{"Add a goat", MenuState::APPEND},
    {"Delete a goat", MenuState::REMOVE},
    {"List goats", MenuState::DISPLAY},
    {"Quit", MenuState::EXIT}
};

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

void Application::append() {
    cout << "Value to insert (float): ";

    string buf;
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

    listy.push_back(number);
    
    cout << format("\nInserted value: {}\n", number);

    state = MAIN_MENU;
}

void Application::remove()  {
    if (listy.size() == 0) {
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

    if (choice < 0 || choice >= listy.size()) {
        cout << "Out of range!\n";
        state = MAIN_MENU;
        return;
    }

    auto it = listy.begin();

    advance(it, choice);

    listy.erase(it);

    cout << "\nDeleted.\n";

    state = MAIN_MENU;
}

void Application::display() {
    cout << "Current list contents:\n";
    
    auto front = listy.begin();
    auto back = listy.end();

    cout << "[ ";

    if (front == back) {
        cout << ']';
    } else {
        while (true) {
            cout << format("{}", *front);

            front++;

            if (front == back) {
                break;
            }

            cout << ", ";
        }

        cout << " ]";
    }

    cout << '\n';

    state = MAIN_MENU;
}

bool Application::parse_int(int& num, const string& input) {
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
