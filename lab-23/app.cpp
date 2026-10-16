#include <iostream>

#include "app.h"
#include "goat.h"

using namespace std;

array<const char*, 25> colors = {
    "Red", "Blue", "Green", "Yellow",
    "Orange", "Purple", "Pink", "Cyan",
    "Magenta", "Lime", "Teal", "Indigo",
    "Violet", "Coral", "Aqua", "Maroon",
    "Olive", "Navy", "Grey", "White",
    "Black", "Beige", "Turquoise", "Silver",
    "Gold"
};

// The assignment didn't say I needed to load this from a file;
// No need to overcomplicate things lol.
array<const char*, 200> names = {
    "Ella", "Inga", "Zane", "Oleg", "Wade", "Yale", "Tami", "Tara",
    "Axel", "Ola","Beth", "Boyd", "Rosa", "Ezra", "Mara", "Rico",
    "Kurt", "Nell", "Cami", "Zeke", "Yoko", "Bree", "Seth", "Amos",
    "Luke", "Elle", "Kara", "Peg", "Faye", "Jody", "Effy", "Cici",
    "Vivi", "Rene", "Zoie", "Arlo", "Erin", "Pete", "Amy", "Owen",
    "Joel", "Joey", "Rudy", "Luca", "Hana", "Eddy", "Esme", "Lynn",
    "Ruby", "Troy", "Macy", "Rosy", "Joni", "Dean", "Cleo", "Dora",
    "Wynn", "Olga", "Jeri", "John", "Gary", "Cara", "Abby", "Chad",
    "Adam", "Kian", "Lori", "Yola", "Erik", "Milo", "Katy", "Sam",
    "Ike", "Eric", "Nina", "Vida", "Neal", "Trey", "Sara", "Mila",
    "Cody", "Zoey", "Cory", "Neil", "Robb", "Lana", "Tala", "Sean",
    "Leon", "Andy", "Fifi", "Mimi", "Jace", "Hans", "Opal", "Finn",
    "Jade", "Vern", "Yuri", "Kyla", "Toby", "Ross", "Saul", "Gael",
    "Juan", "Dale", "Hugo", "Page", "Suki", "Hope", "Tori", "Kase",
    "Ivan", "Lila", "Tina", "Lola", "Vera", "Mark", "Kyle", "Dede",
    "Raul", "Lyle", "Levi", "Dana", "Nora", "Ruth", "Jude", "Nola",
    "Nash", "Kiki", "Anna", "Kole", "Alva", "Sue", "Alex", "Hank",
    "Otis", "Gail", "Paul", "Niko", "Iris", "Ryan", "Ivor", "Jenn",
    "Kirk", "Drew", "Lena", "Sina", "Will", "Umar", "Jett", "Todd",
    "Olin", "Uma", "Ward", "Lara", "Tate", "Pia", "Rena", "Gabe",
    "Oran", "Jill", "Kent", "Bibi", "Abel", "Gigi", "Otto", "Zena",
    "Noah", "Evan", "Rory", "Dane", "Jose", "Lily", "Karl", "Niki",
    "Jack", "Omar", "Liam", "Meg", "Dino", "Olaf", "Josh", "Quin",
    "Ally", "Zara", "Tess", "Zack", "Jake", "Tony", "Glen", "Carl",
    "Alma", "Elmo", "Mae", "Nick", "Marq", "Latt", "Tron", "Zorg"
};

int Application::run() {
    listy = list<Goat>();
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

const array<tuple<const char*, MenuState>, 4> options = {
    tuple{"Add a goat", MenuState::APPEND},
    {"Delete a goat", MenuState::REMOVE},
    {"List goats", MenuState::DISPLAY},
    {"Quit", MenuState::EXIT}
};

void Application::main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";

    for (size_t i = 0; i < options.size(); i++) {
        cout << format("[{}] {}\n", i + 1, get<0>(options[i]));
    }

    state = MAIN_MENU_DECISION;
}

void Application::main_menu_decision() {
    cout << "Choice --> ";
    
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
    cout << "Adding a goat...\n";

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
