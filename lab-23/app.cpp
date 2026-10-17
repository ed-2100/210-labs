#include <iostream>
#include <chrono>
#include <random>
#include <ranges>

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
    while (true) {
        MenuState current;
        
        if (state.size() > 0) {
            current = state.back();
            state.pop_back();
        } else {
            current = MAIN_MENU;
        }

        switch (current) {
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

    state.push_back(MAIN_MENU_DECISION);
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
        state.clear();
        return;
    }

    state.push_back(get<1>(options[choice - 1]));
}

void Application::append() {
    cout << "Adding a goat...";

    auto current_time = chrono::steady_clock::now();

    mt19937 gen(current_time.time_since_epoch().count());

    uniform_int_distribution<uint32_t> dist_names(0, names.size() - 1);
    uniform_int_distribution<uint32_t> dist_age(1, 20);
    uniform_int_distribution<uint32_t> dist_colors(0, colors.size() - 1);
    
    string name = names[dist_names(gen)];
    int age = dist_age(gen);
    string color = colors[dist_colors(gen)];

    Goat goaty(move(name), age, move(color));

    listy.push_back(move(goaty));
    
    cout << " Done.\n";
}

void Application::remove()  {
    if (listy.size() == 0) {
        cout << "No elements to remove.\n";
        return;
    }

    display();

    cout << "\nGoat to remove: ";

    string buf;
    getline(cin, buf);

    int choice;
    if (!parse_int(choice, buf)) {
        state.clear();
        return;
    }

    if (choice < 1 || choice > listy.size()) {
        cout << "Out of range!\n";
        state.clear();
        return;
    }

    auto it = listy.begin();

    advance(it, choice - 1);

    listy.erase(it);

    cout << "\nDeleted.\n";
}

void Application::display() {
    if (listy.size() > 0)
    for (const auto& [i, goat]: views::enumerate(listy)) {
        cout << format(
            "[{}] {} ({}, {})\n",
            i + 1,
            goat.get_name(),
            goat.get_age(),
            goat.get_color()
        );
    } else {
        cout << "No goats.\n";
    }
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
