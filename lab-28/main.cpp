#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <filesystem>
#include <vector>
#include <random>
#include <print>
#include <ranges>

#include "goat.h"

using namespace std;

vector<string> read_lines(const filesystem::path& file);

template <typename Rng>
Goat random_goat(
    Rng& gen,
    span<const string> names,
    span<const string> colors
);

template <typename Rng>
list<Goat> random_trip(
    Rng& gen,
    span<const string> names,
    span<const string> colors
);

void display_trip(const list<Goat>& trip);

bool parse_int(const string& src, int& dst);

int choose_number(int min, int max);

int select_goat(list<Goat> trip);

int main_menu();

template <typename Rng>
void append_goat(
    list<Goat> &trip,
    Rng& gen,
    span<const string> names,
    span<const string> colors
);

void remove_goat(list<Goat>& trip);

int main(int argc, const char** argv) {
    auto current_time = chrono::steady_clock::now();
    mt19937 gen(current_time.time_since_epoch().count());

    auto exe_file = filesystem::path(argv[0]);
    auto exe_dir = exe_file.parent_path();
    auto names_file = exe_dir / "names.txt";
    auto colors_file = exe_dir / "colors.txt";

    vector<string> names = read_lines(names_file);
    vector<string> colors = read_lines(colors_file);
    list<Goat> trip = random_trip(gen, names, colors);

    // Goat Manager 3001 Engine
    int sel = 0;
    while (sel != 12) {
        sel = main_menu();

        switch (sel) {
            case 1: append_goat(trip, gen, names, colors); break;
            case 6: remove_goat(trip); break;
            case 9: 
                println("\nCurrent trip:");
                display_trip(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }

        println();
    }

    return 0;
}

vector<string> read_lines(const filesystem::path& file) {
    vector<string> lines;

    ifstream f(file);

    if (f.fail()) {
        throw runtime_error(format("Failed to open {}", file.c_str()));
    }

    string buf;
    while (getline(f, buf)) {
        lines.push_back(move(buf));
    }

    return lines;
};

template <typename Rng>
Goat random_goat(
    Rng& gen,
    span<const string> names,
    span<const string> colors
) {
    uniform_int_distribution<size_t> dist_names(0, names.size() - 1);
    uniform_int_distribution<uint32_t> dist_age(1, 20);
    uniform_int_distribution<size_t> dist_colors(0, colors.size() - 1);

    return Goat(
        names[dist_names(gen)],
        dist_age(gen),
        colors[dist_colors(gen)]
    );
}

template <typename Rng>
list<Goat> random_trip(
    Rng& gen,
    span<const string> names,
    span<const string> colors
) {
    list<Goat> trip;

    uniform_int_distribution<size_t> dist_size(8, 15);
    int tripSize = dist_size(gen);

    for (size_t i = 0; i < tripSize; i++) {
        trip.push_back(random_goat(gen, names, colors));
    }

    return trip;
}

void display_trip(const list<Goat>& trip) {
    for (auto [i, gt]: views::enumerate(trip)) {
        println(
            "    [{}] {} ({}, {})",
            i + 1,
            gt.get_name(),
            gt.get_age(),
            gt.get_color()
        );
    }
}

bool parse_int(const string& src, int& dst) {
    try {
        dst = stoi(src);
    } catch (invalid_argument) {
        println("\nNot a valid number.");
        return false;
    } catch (out_of_range) {
        println("\nDefinitely out of range.");
        return false;
    }

    return true;
}

int choose_number(int min, int max) {
    int choice;

    while (true) {
        print("\nChoice --> ");

        string buf;
        getline(cin, buf);

        if (!parse_int(buf, choice)) continue;
        
        if (choice < min || choice > max) {
            println("\nOut of range, try again.");
        }

        break;
    }

    return choice;
}

int select_goat(list<Goat> trip) {
    println("Make a selection:");
    
    display_trip(trip);
    
    return choose_number(1, trip.size());
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n"
            "[1 ] Append goat               (pre-existing)\n"
            // "[2 ] Prepend goat              (1st new)\n"
            // "[3 ] Remove first goat         (2nd new)\n"
            // "[4 ] Remove last goat          (3rd new)\n"
            // "[5 ] Insert goat before number (4th new)\n"
            "[6 ] Remove goat at number     (pre-existing)\n"
            // "[7 ] Sort goats                (5th new)\n"
            // "[8 ] Find goat                 (6th new)\n"
            "[9 ] Display trip              (pre-existing)\n"
            // "[10] Reverse goats             (7th new)\n"
            // "[11] Clear goats               (8th new)\n"
            "[12] Exit                      (pre-existing)\n";

    return choose_number(1, 12);
}

template <typename Rng>
void append_goat(
    list<Goat> &trip,
    Rng& gen,
    span<const string> names,
    span<const string> colors
) {
    println("\nAPPEND A GOAT");

    trip.push_back(random_goat(gen, names, colors));

    println("\nGoat appended. New trip size: {}", trip.size());
}

void remove_goat(list<Goat> &trip) {
    println("\nREMOVE A GOAT");

    int index = select_goat(trip);
    trip.erase(next(trip.begin(), index - 1));

    println("\nGoat deleted. New trip size: {}", trip.size());
}
