// COMSC-210 | Lab 11 | Edwin Burwell
//
// Note: This code may or may not use newer C++ features.

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <optional>

using namespace std;

struct KVPair {
    string key;
    string value;
};

struct HashMap {
    vector<vector<KVPair>> storage;
    size_t count;

    optional<string> put(string key, string value);
    string& get(string key);
    string remove(string key);
    void resize(size_t n);
};

optional<string> HashMap::put(string key, string value) {
    if (count >= storage.size()) {
        resize(storage.size() << 1);
    }

    size_t key_hash = hash<string>{}(key);

    size_t idx_broad = key_hash % storage.size();

    auto it_narrow = find(
        storage[idx_broad].begin(),
        storage[idx_broad].end(),
        [&key](auto&& k){
            return key == k;
        }
    );

    if (it_narrow == storage[idx_broad].end()) { // Doesn't exist.
        
    } else { // Already exists.

    }
}

int main() {

}
