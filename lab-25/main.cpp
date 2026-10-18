#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
#include <set>
#include <vector>
#include <memory>
#include <format>

using namespace std;

struct Container {
    virtual ~Container() = default;
    virtual bool read(const char** entries, size_t n) {
        return false;
    }
    virtual bool sort() {
        return false;
    }
    virtual bool insert(const char* entry) {
        return false;
    }
    virtual bool remove() {
        return false;
    }
    virtual const char* name() {
        return nullptr;
    }
};

struct Operation {
    virtual ~Operation() = default;

}

int main(int argc, const char** argv) {
    vector<unique_ptr<Container>> containers;

    const char* operations[] = {
        "READING\0",
        "SORTING\0",
        "INSERTING\0",
        "DELETING\0"
    };

    for (auto& c : containers) {
        const char* name = c->name();

        if (!name) {
            name = "UNKNOWN\0";
        }

        cout << format("Testing {}:", name);

        for (size_t i = 0; i < 4; i++) {
            cout << "    ";

            switch (i) {
                case 0:
                    cout << "READING";
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }
        }
    }
}
