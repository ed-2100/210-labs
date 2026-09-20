// COMSC-210 | Lab 11 | Edwin Burwell
//
// Note: This code may or may not use newer C++ features.

#include <string>
#include <memory>
#include <vector>

using namespace std;

struct KVPair {
    string key;
    string value;
};

struct HashMap {
    vector<vector<KVPair>> storage;
    size_t count;

    void put(string key, string value);
    string& get(string key);
    string remove(string key);
    void resize(size_t n);
};

void HashMap::put(string key, string value) {
    if (count >= storage.size()) {
        resize(storage.size() << 1);
    }

    auto key_hash = hash<string>{}(key);

    
}

int main() {

}
