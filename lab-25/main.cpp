#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
#include <set>
#include <vector>
#include <memory>

using namespace std;

struct Container {
    virtual ~Container() = default;
    virtual void read(const int* const entries, size_t n) = 0;
    virtual void sort() = 0;
    virtual void insert() = 0;
    virtual void remove() = 0;
};

int main(int argc, const char** argv) {
    vector<unique_ptr<Container>> containers;

    for (& c : containers) {

    }
}
