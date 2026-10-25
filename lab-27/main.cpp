#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

int main() {
    // declarations
    map<string, tuple<int, string, string>> villagerColors;

    // insert elements into the map
    // note how the right-hand side of the assignment are the vector elements
    villagerColors["Audie"] = {4, "Goblin", "HAMBURGER"};
    villagerColors["Raymond"] = {7, "Duck", "Got any grapes?"};
    villagerColors.insert({"Marshal", {9, "Human", "My back..."}});

    // access the map using a range-based for loop
    cout << "Villagers and their traits:" << endl;
    for (auto pair : villagerColors) {
        cout << pair.first << ":\n";

        auto& stats = pair.second;

        cout << "    Friendship Level: " << get<0>(stats) << '\n';
        cout << "    Species: " << get<1>(stats) << '\n';
        cout << "    Catchphrase: " << get<2>(stats) << '\n';
    }

    // access the map using iterators
    cout << "\nVillagers and their traits (iterators):" << endl;
    for (auto it = villagerColors.begin(); it != villagerColors.end(); ++it) {
        cout << it->first << ":\n";

        auto& stats = it->second;

        cout << "    Friendship Level: " << get<0>(stats) << '\n';
        cout << "    Species: " << get<1>(stats) << '\n';
        cout << "    Catchphrase: " << get<2>(stats) << '\n';
    }

    // delete an element
    villagerColors.erase("Raymond");

    // search for an element using .find() to avoid errors
    string searchKey = "Audie";
    auto it = villagerColors.find(searchKey);
    if (it != villagerColors.end()) {  // the iterator points to beyond the end of the map
                                       // if searchKey is not found
        cout << "\nFound " << searchKey << "'s traits:\n";

        auto& stats = it->second;

        cout << "    Friendship Level: " << get<0>(stats) << '\n';
        cout << "    Species: " << get<1>(stats) << '\n';
        cout << "    Catchphrase: " << get<2>(stats) << '\n';
    } else
        cout << endl << searchKey << " not found." << endl;

    // report size, clear, report size again to confirm map operations
    cout << "\nSize before clear: " << villagerColors.size() << endl;
    villagerColors.clear();
    cout << "Size after clear: " << villagerColors.size() << endl;

    return 0; // :)
}
