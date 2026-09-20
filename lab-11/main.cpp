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

// The key-value struct.
//
// Holds data associated with a `HashMap` entry.
struct KVPair {
    string key;
    string value;

    // Pre-computed hash to reduce
    // CPU cycles on resize.
    size_t hash;
};

// A simple hashmap made using standard library.
//
// Holds string data with an amoritzed look-up complexity of O(1).
struct HashMap {
    vector<vector<KVPair>> coarse = {};
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
// The value of the original entry, if present.
optional<string> hashmap_put(HashMap& map, string key, string value);

string* hashmap_get(HashMap& map, string key);

optional<string> hashmap_remove(HashMap& map, string key);

void hashmap_resize(HashMap& map, size_t n);

int main() {
    HashMap map;
    string not_found = "Not Found";

    cout << "Homebrew HashMap Implementation\n\n";

    cout << "Setting \"Name\" to \"Edwin\"...";
    hashmap_put(map, "Name", "Edwin");

    cout << " Done.\n\nSetting \"Class\" to \"COMSC 210\"...";
    hashmap_put(map, "Class", "COMSC 210");

    cout << " Done.\n\nSetting \"Shirt Color\" to \"Blue\"...";
    hashmap_put(map, "Shirt Color", "Blue");

    cout << " Done.\n\nGetting \"Name\"...";

    {
        string* maybe_name = hashmap_get(map, "Name");
        cout << "\nName: "
                << (maybe_name ? *maybe_name : not_found);
    }

    cout << "\n\nSetting \"Name\" to \"Charles\"...\n"
         << "Old Name: "
         << hashmap_put(map, "Name", "Charles").value_or(not_found);

    cout << "\n\nRemoving \"Name\"...\nOld Name: "
         << hashmap_remove(map, "Name").value_or(not_found);

    cout << "\n\nGetting \"Name\"...";

    {
        string* maybe_name = hashmap_get(map, "Name");
        cout << "\nName: "
             << (maybe_name ? *maybe_name : not_found);
    }

    cout << "\n\nGetting \"Class\"...";

    {
        string* maybe_class = hashmap_get(map, "Class");
        cout << "\nClass: "
             << (maybe_class ? *maybe_class : not_found);
    }

    cout << "\n\nGetting \"Shirt Color\"...";

    {
        string* maybe_class = hashmap_get(map, "Shirt Color");
        cout << "\nShirt Color: "
             << (maybe_class ? *maybe_class : not_found)
             << '\n';
    }
}

optional<string> hashmap_put(HashMap& map, string key, string value) {
    if (map.count >= map.coarse.size()) {
        size_t n = map.coarse.size() == 0 ? 1 : map.coarse.size();
        hashmap_resize(map, n);
    }

    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % map.coarse.size();

    vector<KVPair>& fine = map.coarse[idx_broad];

    auto it_narrow = find_if(
        fine.begin(),
        fine.end(),
        [&key](KVPair& p){
            return key == p.key;
        }
    );

    if (it_narrow == fine.end()) { // Doesn't exist.
        fine.push_back(KVPair {
            .key = move(key),
            .value = move(value),
            .hash = key_hash,
        });

        return {};
    } else { // Already exists.
        return exchange(it_narrow.base()->value, value);
    }
}

string* hashmap_get(HashMap& map, string key) {
    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % map.coarse.size();

    vector<KVPair>& fine = map.coarse[idx_broad];

    auto it_narrow = find_if(
        fine.begin(),
        fine.end(),
        [&key](KVPair& p){
            return key == p.key;
        }
    );

    if (it_narrow == fine.end()) { // Doesn't exist.
        return {};
    } else { // Exists.
        return &it_narrow.base()->value;
    }
}

optional<string> hashmap_remove(HashMap& map, string key) {
    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % map.coarse.size();

    vector<KVPair>& fine = map.coarse[idx_broad];

    auto it_narrow = find_if(
        fine.begin(),
        fine.end(),
        [&key](KVPair& p){
            return key == p.key;
        }
    );

    if (it_narrow == fine.end()) { // Doesn't exist.
        return {};
    } else { // Exists.
        KVPair p = exchange(*it_narrow.base(), move(fine.back()));
        
        // Wish this function would just return
        // the value of the thing it removed.
        fine.pop_back();
        
        return p.value;
    }
}

void hashmap_resize(HashMap& map, size_t n) {
    if (n <= map.coarse.size()) {
        return;
    }

    vector<vector<KVPair>> coarse_new;
    coarse_new.resize(n);

    for (auto&& fine : map.coarse) {
        for (auto&& item : fine) {
            size_t idx_broad = item.hash % coarse_new.size();
            coarse_new[idx_broad].push_back(move(item));
        }
    }

    map.coarse = move(coarse_new);
}
