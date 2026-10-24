// COMSC-210 | Lab 26 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
#include <set>
#include <vector>
#include <memory>
#include <format>
#include <span>
#include <filesystem>
#include <ranges>
#include <concepts>
#include <algorithm>
#include <array>

#include "benchmark.h"

using namespace std;

// The `main` function.
//
// Benchmarks operations of various containers and subsequently
// displays the results to `stdout`.
//
// ### Arguments
//
// - `argc`: The length of `argv`.
// - `argv`: The arguments passed to the program.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main(int argc, const char** argv) {
    vector<string> data;

    auto exe_file = filesystem::path(argv[0]);
    auto exe_dir = exe_file.parent_path();
    auto input_file = exe_dir / "codes.txt";

    ifstream file(input_file);
    string buf;
    while (getline(file, buf)) {
        data.push_back(buf);
    }

    benchmark<Populate, Sort, Insert, Remove>(
        data,
        Container<list<const char*>>{"list"},
        Container<vector<const char*>>{"vector"},
        Container<set<const char*>>{"set"}
    );

    return EXIT_SUCCESS; // :)
}
