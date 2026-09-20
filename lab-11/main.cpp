// COMSC-210 | Lab 11 | Edwin Burwell
//
// Note: This code may or may not use newer C++ features.

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <optional>
#include <utility>

using namespace std;

struct KVPair {
    string key;
    string value;

    // Stored pre-computed in order to reduce CPU cycles on resize.
    size_t hash;
};

struct HashMap {
    vector<vector<KVPair>> coarse;
    size_t count;
};

optional<string> hashmap_put(HashMap& map, string key, string value) {
    if (map.count >= map.coarse.size()) {
        hashmap_resize(map, map.coarse.size() << 1);
    }

    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % map.coarse.size();

    vector<KVPair>& fine = map.coarse[idx_broad];

    auto it_narrow = find(
        fine.begin(),
        fine.end(),
        [&key](auto&& k){
            return key == k;
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

optional<string*> hashmap_get(HashMap& map, string key) {
    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % map.coarse.size();

    vector<KVPair>& fine = map.coarse[idx_broad];

    auto it_narrow = find(
        fine.begin(),
        fine.end(),
        [&key](auto&& k){
            return key == k;
        }
    );

    if (it_narrow == fine.end()) { // Doesn't exist.
        return {};
    } else { // Exists.
        return &it_narrow.base()->value;
    }
}

optional<string> hashmap_remove(HashMap map, string key) {
    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % map.coarse.size();

    vector<KVPair>& fine = map.coarse[idx_broad];

    auto it_narrow = find(
        fine.begin(),
        fine.end(),
        [&key](auto&& k){
            return key == k;
        }
    );

    if (it_narrow == fine.end()) { // Doesn't exist.
        return {};
    } else { // Exists.
        KVPair p = exchange(*it_narrow.base(), move(fine.back()));
        fine.pop_back();
        return p.value;
    }
}

void hashmap_resize(HashMap map, size_t n) {
    if (n <= map.coarse.size()) {
        return;
    }

    vector<vector<KVPair>> coarse_new{};
    coarse_new.resize(n);

    for (auto&& fine : map.coarse) {
        for (auto&& item : fine) {
            size_t idx_broad = item.hash % coarse_new.size();
            coarse_new[idx_broad].push_back(move(item));
        }
    }

    map.coarse = coarse_new;
}

int main() {

}
