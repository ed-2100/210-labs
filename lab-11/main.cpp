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
};

struct HashMap {
    vector<vector<KVPair>> coarse;
    size_t count;

    optional<string> put(string key, string value);
    optional<string*> get(string key);
    string remove(string key);
    void resize(size_t n);
};

optional<string> HashMap::put(string key, string value) {
    if (count >= coarse.size()) {
        resize(coarse.size() << 1);
    }

    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % coarse.size();

    vector<KVPair>& fine = coarse[idx_broad];

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
            .value = move(value)
        });

        return {};
    } else { // Already exists.
        return exchange(it_narrow.base()->value, value);
    }
}

optional<string*> HashMap::get(string key) {
    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % coarse.size();

    vector<KVPair>& fine = coarse[idx_broad];

    auto it_narrow = find(
        fine.begin(),
        fine.end(),
        [&key](auto&& k){
            return key == k;
        }
    );


    if (it_narrow == fine.end()) { // Doesn't exist.
        return {};
    } else { // Already exists.
        return exchange(it_narrow.base()->value, value);
    }
}

int main() {

}
