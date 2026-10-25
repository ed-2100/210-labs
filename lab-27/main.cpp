#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

bool parse_int(const string& src, int& dst) {
    try {
        dst = stoi(src);
    } catch (invalid_argument) {
        cout << "Not a valid number.\n";
        return false;
    } catch (out_of_range) {
        cout << "Definitely out of range.\n";
        return false;
    }

    return true;
}

int main() {
    // declarations
    map<string, tuple<int, string, string>> villagers;

    // insert elements into the map
    // note how the right-hand side of the assignment are the vector elements
    villagers["Audie"] = {4, "Goblin", "HAMBURGER"};
    villagers["Raymond"] = {7, "Duck", "Got any grapes?"};
    villagers.insert({"Marshal", {9, "Human", "My back..."}});

    // // access the map using a range-based for loop

    // // access the map using iterators
    // cout << "\nVillagers and their traits (iterators):" << endl;
    // for (auto it = villagers.begin(); it != villagers.end(); ++it) {
    //     cout << it->first << ":\n";

    //     auto& stats = it->second;

    //     cout << "    Friendship Level: " << get<0>(stats) << '\n';
    //     cout << "    Species: " << get<1>(stats) << '\n';
    //     cout << "    Catchphrase: " << get<2>(stats) << '\n';
    // }

    // // delete an element
    // villagers.erase("Raymond");

    // // search for an element using .find() to avoid errors
    // string searchKey = "Audie";
    // auto it = villagers.find(searchKey);
    // if (it != villagers.end()) {  // the iterator points to beyond the end of the map
    //                                    // if searchKey is not found
    //     cout << "\nFound " << searchKey << "'s traits:\n";

    //     auto& stats = it->second;

    //     cout << "    Friendship Level: " << get<0>(stats) << '\n';
    //     cout << "    Species: " << get<1>(stats) << '\n';
    //     cout << "    Catchphrase: " << get<2>(stats) << '\n';
    // } else
    //     cout << endl << searchKey << " not found." << endl;

    // // report size, clear, report size again to confirm map operations
    // cout << "\nSize before clear: " << villagers.size() << endl;
    // villagers.clear();
    // cout << "Size after clear: " << villagers.size() << endl;

    string buf;
    int choice;
    bool should_exit = false;

    while (!should_exit) {
        cout << "Villagers and their traits:" << endl;
        for (auto pair : villagers) {
            cout << pair.first << ":\n";

            auto& stats = pair.second;

            cout << "    Friendship Level: " << get<0>(stats) << '\n';
            cout << "    Species: " << get<1>(stats) << '\n';
            cout << "    Catchphrase: " << get<2>(stats) << '\n';
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
                cout << "Of who? ";
                cin >> buf;

                auto& villager = villagers[buf];

                cout << "By how much? ";
                cin >> buf;

                int d_friendship;
                if (!parse_int(buf, d_friendship)) {
                    break;
                }

                if (d_friendship < 0 || get<0>(villager) + d_friendship > 10) {
                    
                }

                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                cout << "Exiting...\n";
                should_exit = true;
                break;
            }
            default: {
                cout << "Invalid choice.\n";
            }
        }
    }

    cout << "\nGoodbye.\n";

    return 0; // :)
}
