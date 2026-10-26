// COMSC-210 | Lab 28 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

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

// Reads the lines of a file and returns them in a `vector`.
//
// ### Arguments
//
//  - `file`: The path of the file to be read.
//
// ### Returns
vector<string> read_lines(const filesystem::path& file);

// Generates a random goat.
//
// ### Arguments
//
// - `gen`: Random number generator to be used
// - `names`: List of names to sample from
// - `colors`: List of colors to sample from
//
// ### Returns
//
// The goat.
template <typename Rng>
Goat random_goat(
    Rng& gen,
    span<const string> names,
    span<const string> colors
);

// Generates a random trip full of goats.
//
// ### Arguments
//
// - `gen`: Random number generator to be used
// - `names`: List of names to sample from
// - `colors`: List of colors to sample from
//
// ### Returns
//
// A trip full of goats.
template <typename Rng>
list<Goat> random_trip(
    Rng& gen,
    span<const string> names,
    span<const string> colors
);

// Prints a trip to `stdout`.
//
// ### Arguments
//
// - `trip`: The trip
void display_trip(const list<Goat>& trip);

// Helper for parsing integers.
//
// Prints an error mesage when invalid input is given.
//
// ### Arguments
//
//  - `src`: String to parse
//  - `dst`: Destination to store the parsed integer
//
// ### Returns
//
// True when parsing was successful.
bool parse_int(const string& src, int& dst);

// Prompts the user to pick a number in `[min, max]`.
//
// ### Arguments
//
//  - `min`: The minimum allowed number
//  - `max`: The maximum allowed number
//
// ### Returns
//
// The chosen number.
int choose_number(int min, int max);

// Prompts the user to select a goat from a trip.
//
// ### Arguments
//
// - `trip`: The trip
//
// ### Returns
//
// The number of the goat chosen.
int select_goat(list<Goat> trip);

// Prints a list of trip operations and prompts the user to make a decision.
//
// ### Returns
//
// The number of the operation decided upon.
//
int main_menu();

// Prepends a goat to the provided trip and displays helpful logs.
//
// ### Arguments
//
// - `trip`: The trip
// - `gen`: Random number generator to be used
// - `names`: List of names to sample from
// - `colors`: List of colors to sample from
template <typename Rng>
void prepend_goat(
    list<Goat>& trip,
    Rng& gen,
    span<const string> names,
    span<const string> colors
);

// Appends a goat to the provided trip and displays helpful logs.
//
// ### Arguments
//
// - `trip`: The trip
// - `gen`: Random number generator to be used
// - `names`: List of names to sample from
// - `colors`: List of colors to sample from
template <typename Rng>
void append_goat(
    list<Goat> &trip,
    Rng& gen,
    span<const string> names,
    span<const string> colors
);

// Inserts a goat in the provided trip at a user-selected
// location while displaying helpful logs.
//
// ### Arguments
//
// - `trip`: The trip
// - `gen`: Random number generator to be used
// - `names`: List of names to sample from
// - `colors`: List of colors to sample from
template <typename Rng>
void insert_goat(
    list<Goat>& trip,
    Rng& gen,
    span<const string> names,
    span<const string> colors
);

// Removes the first goat in the provided trip and displays helpful logs.
//
// ### Arguments
//
// - `trip`: The trip
void remove_first_goat(list<Goat>& trip);

// Removes the last goat in the provided trip and displays helpful logs.
//
// ### Arguments
//
// - `trip`: The trip
void remove_last_goat(list<Goat>& trip);

// Removes a user-selected goat from the provided
// trip while displaying helpful logs.
//
// ### Arguments
//
// - `trip`: The trip
void remove_goat(list<Goat>& trip);

// Sorts the provided trip while displaying helpful logs.
//
// ### Arguments
//
// - `trip`: The trip
void sort_trip(list<Goat>& trip);

// Finds a user-specified goat by name and reports the goat's details to the user.
//
// ### Arguments
//
// - `trip`: The trip
void find_goat(list<Goat>& trip);

// Reverses the provided trip while displaying helpful logs.
//
// ### Arguments
//
// - `trip`: The trip
void reverse_trip(list<Goat>& trip);

// Clears the provided trip and displays helpful logs.
//
// ### Arguments
//
// - `trip`: The trip
void clear_trip(list<Goat>& trip);

// The `main` function.
//
// Demonstrates STL algorithms using a goat trip scenario.
//
// ### Arguments
//
// - `argc`: The length of `argv`.
// - `argv`: The arguments passed to the program.
//
// ### Returns
//
// A signed integer value, where `0` means success.
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

        println();

        switch (sel) {
            case 1: prepend_goat(trip, gen, names, colors); break;
            case 2: append_goat(trip, gen, names, colors); break;
            case 3: insert_goat(trip, gen, names, colors); break;
            case 4: remove_first_goat(trip); break;
            case 5: remove_last_goat(trip); break;
            case 6: remove_goat(trip); break;
            case 7: sort_trip(trip); break;
            case 8: find_goat(trip); break;
            case 9: 
                println("Current trip:");
                display_trip(trip);
                break;
            case 10: reverse_trip(trip); break;
            case 11: clear_trip(trip); break;
            case 12: println("Exiting..."); break;
            default:
                cout << "Invalid selection.\n";
                break;
        }

        println();
    }

    return 0; // :)
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
    for (auto [i, gt]: trip | views::enumerate) {
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
        print("Choice --> ");

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
            "[1 ] Prepend goat              (1st new)\n"
            "[2 ] Append goat               (pre-existing)\n"
            "[3 ] Insert goat before goat   (2nd new)\n"
            "[4 ] Remove first goat         (3rd new)\n"
            "[5 ] Remove last goat          (4th new)\n"
            "[6 ] Remove custom goat        (pre-existing)\n"
            "[7 ] Sort trip                 (5th new)\n"
            "[8 ] Find goat                 (6th new)\n"
            "[9 ] Display trip              (pre-existing)\n"
            "[10] Reverse trip              (7th new)\n"
            "[11] Clear trip                (8th new)\n"
            "[12] Exit                      (pre-existing)\n";

    return choose_number(1, 12);
}

template <typename Rng>
void prepend_goat(
    list<Goat>& trip,
    Rng& gen,
    span<const string> names,
    span<const string> colors
) {
    println("PREPEND A GOAT");

    trip.push_front(random_goat(gen, names, colors));

    println("Goat prepended. New trip size: {}", trip.size());
}

template <typename Rng>
void append_goat(
    list<Goat> &trip,
    Rng& gen,
    span<const string> names,
    span<const string> colors
) {
    println("APPEND A GOAT");

    trip.push_back(random_goat(gen, names, colors));

    println("Goat appended. New trip size: {}", trip.size());
}

template <typename Rng>
void insert_goat(
    list<Goat>& trip,
    Rng& gen,
    span<const string> names,
    span<const string> colors
) {
    println("INSERT A GOAT");

    println("Decide where to insert:");
    display_trip(trip);

    trip.insert(
        next(
            trip.begin(),
            choose_number(1, trip.size()) - 1
        ),
        random_goat(gen, names, colors)
    );

    println("Goat appended. New trip size: {}", trip.size());
}

void remove_first_goat(list<Goat>& trip) {
    println("REMOVE FIRST GOAT");

    trip.pop_front();

    println("First goat deleted. New trip size: {}", trip.size());
}

void remove_last_goat(list<Goat>& trip) {
    println("REMOVE LAST GOAT");

    trip.pop_back();

    println("Last goat deleted. New trip size: {}", trip.size());
}

void remove_goat(list<Goat>& trip) {
    println("REMOVE A GOAT");

    int index = select_goat(trip);
    trip.erase(next(trip.begin(), index - 1));

    println("Goat deleted. New trip size: {}", trip.size());
}

void sort_trip(list<Goat>& trip) {
    println("SORT TRIP");

    trip.sort();

    println("Trip sorted.");
}

void find_goat(list<Goat>& trip) {
    println("FIND GOAT");

    print("Name (case sensitive): ");

    string buf;
    getline(cin, buf);

    auto view = trip | views::enumerate;

    auto it = ranges::find_if(
        view,
        [&](const auto& temp) {
            const auto& [i, gt] = temp;
            return gt.get_name() == buf;
        }
    );

    if (it != view.end()) {
        const auto& [i, gt] = *it;
        println(
            "Found goat {}: {} ({}, {})",
            i + 1,
            gt.get_name(),
            gt.get_age(),
            gt.get_color()
        );
    } else {
        println("Goat not found.");
    }
}

void reverse_trip(list<Goat>& trip) {
    println("REVERSE TRIP");

    trip.reverse();

    println("Trip reversed.");
}

void clear_trip(list<Goat>& trip) {
    println("CLEAR TRIP");

    trip.clear();

    println("Trip cleared.");
}
