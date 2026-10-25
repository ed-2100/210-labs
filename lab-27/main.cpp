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
                "1. Add Villager\n"
                "2. Delete Villager\n"
                "3. Increase Friendship\n"
                "4. Decrease Friendship\n"
                "5. Search for Villager\n"
                "6. Exit\n"
                "Enter choice: ";
        
        getline(cin, buf);

        int choice;
        if (!parse_int(buf, choice)) {
            continue;
        }

        switch (choice) {
            case 1: {
                string name;
                cout << "Villager name: ";
                getline(cin, name);

                if (villagers.find(name) != villagers.end()) {
                    cout << '\n' << name << " already exists.\n";
                    break;
                }

                cout << "Friendship level: ";
                getline(cin, buf);

                int friendship_level;
                if (!parse_int(buf, friendship_level)) {
                    break;
                }

                if (friendship_level < 0 || friendship_level > 10) {
                    cout << "\nOut of range.\n";
                    break;
                }

                string species;
                cout << "Species: ";
                getline(cin, species);

                string catchphrase;
                cout << "Catchphrase: ";
                getline(cin, catchphrase);

                villagers.insert({
                    name, tuple {
                        friendship_level,
                        move(species),
                        move(catchphrase)
                    }
                });

                cout << '\n' << name << " added.\n";

                break;
            }
            case 2: {
                cout << "Who? ";
                getline(cin, buf);

                if (villagers.erase(buf) == 0) {
                    cout << '\n' << buf << " does not exist.\n";
                    break;
                }

                cout << '\n' << buf << " deleted.\n";

                break;
            }
            case 3: case 4: {
                cout << "Of who? ";
                getline(cin, buf);

                auto it = villagers.find(buf);

                if (it == villagers.end()) {
                    cout << "\nThat villager doesn't exist.\n";
                    break;
                }

                auto& villager = it->second;

                cout << "By how much? ";
                getline(cin, buf);

                int d_friendship;
                if (!parse_int(buf, d_friendship)) {
                    break;
                }

                int friendship_level = get<0>(villager);
                
                if (choice == 3) {
                    friendship_level += d_friendship;
                } else {
                    friendship_level -= d_friendship;
                }

                if (d_friendship < 0 || friendship_level < 0 || friendship_level > 10) {
                    cout << "\nOut of range.\n";
                    break;
                }

                get<0>(villager) = friendship_level;

                cout << "\nFriendship adjusted.\n";

                break;
            }
            case 5: {
                cout << "Who? ";
                getline(cin, buf);

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
                cout << "\nExiting...\n\n";
                should_exit = true;
                break;
            }
            default: {
                cout << "\nInvalid choice.\n";
            }
        }
    }

    return 0; // :-)
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
