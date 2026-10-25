// COMSC-210 | Lab 27 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

// Helper for parsing integers from user input.
//
// ### Arguments
//
//  - `src`: Input to parse
//  - `dst`: Variable to store the parsed input in
//
// ### Returns
//
// A boolean, which is true on successful parsing.
bool parse_int(const string& src, int& dst);

// The `main` function.
//
// Demonstrates the standard library's `map` implementation
// using a villager book-keeping scenario.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main() {
    // declarations
    map<string, tuple<int, string, string>> villagers;

    // insert elements into the map
    // note how the right-hand side of the assignment are the vector elements
    villagers["Audie"] = {4, "Goblin", "HAMBURGER"};
    villagers["Raymond"] = {7, "Duck", "Got any grapes?"};
    villagers.insert({"Marshal", {9, "Human", "My back..."}});

    cout << "========================\n"
            "===== Villager Map =====\n"
            "========================\n";

    string buf;
    int choice;
    bool should_exit = false;

    while (!should_exit) {
        cout << "\nVillager details:" << endl;
        for (auto pair : villagers) {
            cout << pair.first << ":\n";

            auto& stats = pair.second;

            cout << "    Friendship Level: " << get<0>(stats) << '\n'
                 << "    Species: " << get<1>(stats) << '\n'
                 << "    Catchphrase: " << get<2>(stats) << '\n';
        }

        cout << "\n"
                "1. Increase Friendship\n"
                "2. Decrease Friendship\n"
                "3. Search for Villager\n"
                "4. Exit\n"
                "Enter choice: ";
        
        cin >> buf;
        if (!parse_int(buf, choice)) {
            continue;
        }

        switch (choice) {
            case 1: {
                string name;
                int friendship_level;
                string species;
                string catchphrase;

                cout << "Villager name: ";
                cin >> name;

                cout << "Friendship level: ";
                cin >> buf;

                if (!parse_int(buf, friendship_level)) {
                    break;
                }

                if (friendship_level < 0 || friendship_level > 10) {
                    cout << "\nOut of range.\n";
                    break;
                }

                cout << "Species: ";
                cin >> species;

                cout << "Catchphrase: ";
                cin >> catchphrase;

                villagers.insert({
                    name, {
                        friendship_level,
                        move(species),
                        move(catchphrase)
                    }
                });

                cout << name << " added.";

                break;
            }
            case 2: {
                cout << "Who? ";
                cin >> buf;

                if (villagers.erase(buf) == 0) {
                    cout << buf << " does not exist.";
                }

                cout << " "

                break;
            }
            case 3: case 4: {
                cout << "Of who? ";
                cin >> buf;

                auto it = villagers.find(buf);

                if (it == villagers.end()) {
                    cout << "\nThat villager doesn't exist.\n";
                    break;
                }

                auto& villager = it->second;

                cout << "By how much? ";
                cin >> buf;

                int d_friendship;
                if (!parse_int(buf, d_friendship)) {
                    break;
                }

                int temp = get<0>(villager);
                
                if (choice == 3) {
                    temp += d_friendship;
                } else {
                    temp -= d_friendship;
                }

                if (d_friendship < 0 || temp < 0 || temp > 10) {
                    cout << "\nOut of range.\n";
                    break;
                }

                get<0>(villager) = temp;

                cout << "\nFriendship adjusted.\n";

                break;
            }
            case 5: {
                cout << "Who? ";
                cin >> buf;

                auto it = villagers.find(buf);
                if (it == villagers.end()) {
                    cout << '\n' << buf << " not found.\n";
                    break;
                }
            
                cout << "\nFound " << buf << "'s details:\n";

                auto& stats = it->second;

                cout << "    Friendship Level: " << get<0>(stats) << '\n'
                     << "    Species: " << get<1>(stats) << '\n'
                     << "    Catchphrase: " << get<2>(stats) << '\n';

                break;
            }
            case 6: {
                cout << "\nExiting...\n";
                should_exit = true;
                break;
            }
            default: {
                cout << "\nInvalid choice.\n";
            }
        }
    }

    cout << "\nGoodbye.\n\n";

    return 0; // :)
}

bool parse_int(const string& src, int& dst) {
    try {
        dst = stoi(src);
    } catch (invalid_argument) {
        cout << "\nNot a valid number.\n";
        return false;
    } catch (out_of_range) {
        cout << "\nDefinitely out of range.\n";
        return false;
    }

    return true;
}
