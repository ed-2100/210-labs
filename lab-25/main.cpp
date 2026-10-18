#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
#include <set>
#include <vector>
#include <memory>
#include <format>
#include <span>

using namespace std;

template <typename Container, typename Func>
void read(Container& container, Func func, span<const char*> data) {
    for (const char* d : data)
    func(container, data)
}

int main(int argc, const char** argv) {

    list<const char*> listy;
    string storage;
    vector<const char*> data;

    read(listy, [](){}, data);
}
