#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <filesystem>
#include <vector>
#include <random>

#include "goat.h"

using namespace std;

// 1.  Append goat               (pre-existing)
// 2.  Prepend goat              (1st new)
// 3.  Remove first goat         (2nd new)
// 4.  Remove last goat          (3rd new)
// 5.  Insert goat before number (4th new)
// 6.  Remove goat at number     (pre-existing)
// 7.  Sort goats                (5th new)
// 8.  Find goat                 (6th new)
// 9.  List goats                (pre-existing)
// 10. Reverse goats             (7th new)
// 11. Clear goats               (8th new)
// 12. Exit                      (pre-existing)

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

template <typename Rng>
Goat random_goat(Rng& gen);

template <typename Rng>
list<Goat> populate_goats(names, Rng& gen) {

}

int main(int argc, const char** argv) {
    auto current_time = chrono::steady_clock::now();
    mt19937 gen(current_time.time_since_epoch().count());

    auto exe_file = filesystem::path(argv[0]);
    auto exe_dir = exe_file.parent_path();
    auto names_file = exe_dir / "names.txt";
    auto colors_file = exe_dir / "colors.txt";

    vector<string> names;
    {
        ifstream f(names_file);


        string buf;
        while (getline(f, buf)) {
            names.push_back(move(buf));
        }
    }

    vector<string> colors;
    {
        ifstream f(colors_file);

        string buf;
        while (getline(f, buf)) {
            names.push_back(move(buf));
        }
    }

    list<Goat> trip;
    {
        uniform_int_distribution<size_t> dist_size(8, 15);
        int tripSize = dist_size(gen);

        for (size_t i = 0; i < tripSize; i++) {

            trip.push_back(random_goat(gen));
        }
    }

    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 4) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, gen, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

template <typename Rng>
void add_goat(list<Goat> &trip, Rng& gen, span<const string> names, span<const string> colors) {
    cout << "ADD A GOAT\n";
    trip.push_back(random_goat(gen));
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

template <typename Rng>
Goat random_goat(Rng& gen) {
    uniform_int_distribution<size_t> dist_names(0, names.size() - 1);
    uniform_int_distribution<uint32_t> dist_age(1, 20);
    uniform_int_distribution<size_t> dist_colors(0, colors.size() - 1);

    Goat goat {
        names[dist_names(gen)],
        dist_age(gen),
        colors[dist_colors(gen)]
    };
}
