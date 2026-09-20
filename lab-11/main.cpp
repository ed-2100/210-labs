// COMSC-210 | Lab 11 | Edwin Burwell
//
// Note: This code may or may not use newer C++ features.

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <optional>
#include <utility>
#include <iostream>

using namespace std;

// Personal data struct.
//
// Holds data related to a person.
struct PersonalInfo {
    string name;
    string age;
    string favorite_color;
    vector<string> inventory;
};

// The key-value struct.
//
// Holds data associated with a `HashMap` entry.
template <typename T>
struct KVPair {
    string key;
    T value;

    // Pre-computed hash to reduce
    // CPU cycles on resize.
    size_t hash;
};

// A simple hashmap made using standard library.
//
// Holds string data with an amoritzed look-up complexity of O(1).
template <typename T>
struct HashMap {
    vector<vector<KVPair<T>>> coarse = {};
    size_t count = 0;
};

// Puts an entry on a `HashMap`.
//
// ### Arguments
//
// - `map`: The `HashMap` to put the entry on.
// - `key`: The key to the entry.
// - `value`: The value the entry contains.
//
// ### Returns
//
// The original value of the entry, if present.
template <typename T>
optional<T> hashmap_put(HashMap<T>& map, string key, string value);

// Gets a pointer to an entry's value in a `HashMap`.
//
// ### Arguments
//
// - `map`: The `HashMap` to get the entry from.
// - `key`: The key to the entry.
//
// ### Returns
//
// A pointer to the entry's value, null if not found.
template <typename T>
T* hashmap_get(const HashMap<T>& map, string key);

// Removes an entry in a `HashMap`.
//
// ### Arguments
//
// - `map`: The `HashMap` to remove the entry from.
// - `key`: The key to the entry.
//
// ### Returns
//
// The value of the former entry, if present.
template <typename T>
optional<T> hashmap_remove(HashMap<T>& map, string key);

// Resizes a hashmap to contain exactly `n` buckets.
//
// ### Arguments
//
// - `map`: The `HashMap` to resize.
// - `n`: The target number of buckets.
template <typename T>
void hashmap_resize(HashMap<T>& map, size_t n);

void print_personal_info(const PersonalInfo& pi);

// The main function.
//
// Tests the features of a homebrew `HashMap` implementation.
//
// ### Arguments
//
// - None.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main() {
    HashMap<PersonalInfo> map;
    
    cout << "Homebrew `HashMap` Implementation\n";

    cout << "Setting \"Edwin\" to\n";
    PersonalInfo edwin {
        .name = "Edwin",
        .age = "20",
        .favorite_color = "Blue",
        .inventory = {"Phone", "Pencil", "Keys"}
    };
    print_personal_info(edwin);


    return EXIT_SUCCESS;
}

template <typename T>
optional<T> hashmap_put(HashMap<T>& map, string key, string value) {
    if (map.count >= map.coarse.size()) {
        size_t n = map.coarse.size() == 0 ? 1 : map.coarse.size();
        hashmap_resize(map, n);
    }

    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % map.coarse.size();

    vector<KVPair<T>>& fine = map.coarse[idx_broad];

    auto it_narrow = find_if(
        fine.begin(),
        fine.end(),
        [&key](KVPair<T>& p){
            return key == p.key;
        }
    );

    if (it_narrow == fine.end()) { // Doesn't exist.
        fine.push_back(KVPair<T> {
            .key = move(key),
            .value = move(value),
            .hash = key_hash,
        });

        return {};
    } else { // Already exists.
        return exchange(it_narrow.base()->value, value);
    }
}

template <typename T>
T* hashmap_get(const HashMap<T>& map, string key) {
    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % map.coarse.size();

    vector<KVPair<T>>& fine = map.coarse[idx_broad];

    auto it_narrow = find_if(
        fine.begin(),
        fine.end(),
        [&key](KVPair<T>& p){
            return key == p.key;
        }
    );

    if (it_narrow == fine.end()) { // Doesn't exist.
        return {};
    } else { // Exists.
        return &it_narrow.base()->value;
    }
}

template <typename T>
optional<T> hashmap_remove(HashMap<T>& map, string key) {
    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % map.coarse.size();

    vector<KVPair<T>>& fine = map.coarse[idx_broad];

    auto it_narrow = find_if(
        fine.begin(),
        fine.end(),
        [&key](KVPair<T>& p){
            return key == p.key;
        }
    );

    if (it_narrow == fine.end()) { // Doesn't exist.
        return {};
    } else { // Exists.
        KVPair<T> p = exchange(*it_narrow.base(), move(fine.back()));
        
        // I wish this function would just return
        // the value of the thing it popped.
        fine.pop_back();
        
        return p.value;
    }
}

template <typename T>
void hashmap_resize(HashMap<T>& map, size_t n) {
    vector<vector<KVPair<T>>> coarse_new;
    coarse_new.resize(n);

    for (auto&& fine : map.coarse) {
        for (auto&& item : fine) {
            size_t idx_broad = item.hash % coarse_new.size();
            coarse_new[idx_broad].push_back(move(item));
        }
    }

    map.coarse = move(coarse_new);
}

void print_personal_info(const PersonalInfo& pi) {
    cout << "Name: " << pi.name
         << "\nAge: " << pi.age
         << "\nFavorite Color: " << pi.favorite_color
         << "\nInventory: ";

    if (pi.inventory.size() != 0) {
        cout << pi.inventory[0];

        for (size_t i = 1; i < pi.inventory.size(); i++) {
            cout << ", " << pi.inventory[i];
        }
    }

    cout << '\n';
}
