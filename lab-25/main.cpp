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

using namespace std;

template <typename F>
chrono::high_resolution_clock::duration measure(F f) {
    auto begin = chrono::high_resolution_clock::now();
    f();
    auto end = chrono::high_resolution_clock::now();
    return end - begin;
}

template <typename Cont>
void populate(Cont& cont, span<const string> data) {
    if constexpr (requires { cont.reserve(data.size()); }) {
        cont.reserve(data.size());
    }

}

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
        auto duration = measure([&cont, &data]() {
            for (const auto& i : data) {
                cont.push_back(i.c_str());
            }
        });
    }

    {
        vector<const char*> cont;
        auto duration = measure([&cont, &data]() {
            cont.reserve(data.size());
            for (const auto& i : data) {
                cont.push_back(i.c_str());
            }
        });
    }

    {
        set<const char*> cont;
        auto duration = measure([&cont, &data]() {
            for (const auto& i : data) {
                cont.insert(i.c_str());
            }
        });
    }

    {
        list<const char*> cont;
        for (const auto& i : data) {
            cont.push_back(i.c_str());
        }
        auto duration = measure([&cont, &data]() {
            cont.sort();
        });
    }

    {
        vector<const char*> cont;
        for (const auto& i : data) {
            cont.push_back(i.c_str());
        }
        auto duration = measure([&cont, &data]() {
            sort(cont.begin(), cont.end());
        });
    }

    {
        // No sort for set.
    }

    {
        list<const char*> cont;
        for (const auto& i : data) {
            cont.push_back(i.c_str());
        }
        auto duration = measure([&cont, &data]() {
            auto it = next(cont.begin(), cont.size() >> 1 - 1);
            cont.insert(it, "TESTCODE");
        });
    }

    {
        vector<const char*> cont;
        cont.reserve(data.size());
        for (const auto& i : data) {
            cont.push_back(i.c_str());
        }
        auto duration = measure([&cont, &data]() {
            auto it = next(cont.begin(), cont.size() >> 1 - 1);
            cont.insert(it, "TESTCODE");
        });
    }

    {
        set<const char*> cont;
        cont.insert_range(data | views::transform([](const string& i){ return i.c_str(); }));
        for (const auto& i : data) {
            cont.insert(i.c_str());
        }
        auto duration = measure([&cont, &data]() {
            auto it = next(cont.begin(), cont.size() >> 1 - 1);
            cont.insert(it, "TESTCODE");
        });
    }

    {
        list<const char*> cont;
        for (const auto& i : data) {
            cont.push_back(i.c_str());
        }
        auto duration = measure([&cont, &data]() {
            auto it = next(cont.begin(), cont.size() >> 1 - 1);
            cont.erase(it);
        });
    }

    {
        vector<const char*> cont;
        cont.reserve(data.size());
        for (const auto& i : data) {
            cont.push_back(i.c_str());
        }
        auto duration = measure([&cont, &data]() {
            auto it = next(cont.begin(), cont.size() >> 1 - 1);
            cont.erase(it);
        });
    }

    {
        set<const char*> cont;
        cont.insert_range(data | views::transform([](const string& i){ return i.c_str(); }));
        for (const auto& i : data) {
            cont.insert(i.c_str());
        }
        auto duration = measure([&cont, &data]() {
            for (const auto& i : data) {
                cont.erase(i.c_str());
            }
        });
    }
}
