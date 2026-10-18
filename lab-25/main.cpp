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

using namespace std;

// | NAME   | READING | SORTING | INSERTING | REMOVING |
// | ====== | ======= | ======= | ========= | ======== |
// | list   |         |         |           |          |
// | set    |         |         |           |          |
// | vector |         |         |           |          |

int main(int argc, const char** argv) {
    vector<string> data;

    auto exe_file = filesystem::path(argv[0]);
    auto exe_dir = exe_file.parent_path();
    auto input_file = exe_dir / "input.txt";

    ifstream file(input_file);
    string buf;
    while (getline(file, buf)) {
        data.push_back(buf);
    }

    {
        list<const char*> cont;
        auto begin = chrono::high_resolution_clock::now();
        for (const auto& i : data) {
            cont.push_back(i.c_str());
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - begin;
    }

    {
        vector<const char*> cont;
        auto begin = chrono::high_resolution_clock::now();
        cont.reserve(data.size());
        for (const auto& i : data) {
            cont.push_back(i.c_str());
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - begin;
    }

    {
        set<const char*> cont;
        auto begin = chrono::high_resolution_clock::now();
        for (const auto& i : data) {
            cont.insert(i.c_str());
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - begin;
    }

    {
        list<const char*> cont;
        auto begin = chrono::high_resolution_clock::now();
        cont.sort();
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - begin;
    }

    {
        vector<const char*> cont;
        auto begin = chrono::high_resolution_clock::now();
        sort(cont.begin(), cont.end());
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - begin;
    }

    {
        // No sort for set.
    }

    {
        list<const char*> cont;
        auto begin = chrono::high_resolution_clock::now();
        cont.insert(cont.size() >> 2, "TESTCODE");
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - begin;
    }

    {
        vector<const char*> cont;
        auto begin = chrono::high_resolution_clock::now();
        cont.reserve(data.size());
        for (const auto& i : data) {
            cont.push_back(i.c_str());
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - begin;
    }

    {
        set<const char*> cont;
        auto begin = chrono::high_resolution_clock::now();
        for (const auto& i : data) {
            cont.insert(i.c_str());
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - begin;
    }
    
}
