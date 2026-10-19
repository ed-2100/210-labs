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

using namespace std;

using Duration = chrono::high_resolution_clock::duration;

template <typename F>
Duration measure(F f) {
    auto begin = chrono::high_resolution_clock::now();
    f();
    auto end = chrono::high_resolution_clock::now();
    return end - begin;
}

template <typename Cont>
void populate(Cont& cont, span<const string> data) {
    if constexpr ( requires { cont.reserve(data.size()); } ) {
        cont.reserve(data.size());
    }

    for (const string& s : data) {
        if constexpr ( requires {cont.push_back(s.c_str());} ) {
            cont.push_back(s.c_str());
        } else if constexpr ( requires { cont.insert(s.c_str()); } ) {
            cont.insert(s.c_str());
        } else {
            static_assert(false, "That ain't it.");
        }
    }
}

struct Populate {
    const char* name = "READING";

    template<typename Cont>
    optional<Duration> run(span<const string> data) {
        Cont cont;
        return measure([&cont, &data]() {
            populate(cont, data);
        });
    }
};

struct Sort {
    const char* name = "SORTING";

    template<typename Cont>
    optional<Duration> run(span<const string> data) {
        Cont cont;

        if constexpr ( requires { cont.sort(); } ) {
            populate(cont, data);
            return measure([&cont, &data]() {
                cont.sort();
            });
        } else if constexpr ( requires { ranges::sort(cont); } ) {
            populate(cont, data);
            return measure([&cont, &data]() {
                ranges::sort(cont);
            });
        } else {
            return nullopt;
        }
    }
};

struct Insert {
    const char* name = "INSERTING";

    template<typename Cont>
    optional<Duration> run(span<const string> data) {
        Cont cont;
        populate(cont, data);
        return measure([&cont, &data]() {
            auto it = next(cont.begin(), cont.size() >> 1 - 1);
            cont.insert(it, "TESTCODE");
        });
    }
};

struct Remove {
    const char* name = "REMOVING";

    template<typename Cont>
    optional<Duration> run_remove(span<const string> data) {
        Cont cont;
        populate(cont, data);
        return measure([&cont, &data]() {
            auto it = next(cont.begin(), cont.size() >> 1 - 1);
            cont.erase(it);
        });
    }
};

template <typename Cont>
struct Container {
    using type = Cont;

    const char* name;
};

template <typename ... Op, typename... Cont>
void benchmark(span<const string> data, Container<Cont> ... cont) {
    
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

    benchmark<Populate, Sort, Insert, Remove>(data, Container<list<const char*>>{"list"});

    {
        auto duration = run_populate<list<const char*>>(data);
    }

    {
        auto duration = run_populate<vector<const char*>>(data);
    }

    {
        auto duration = run_populate<set<const char*>>(data);
    }

    {
        auto duration = run_sort<list<const char*>>(data);
    }

    {
        auto duration = run_sort<vector<const char*>>(data);
    }

    {
        auto duration = run_sort<set<const char*>>(data);
    }

    {
        auto duration = run_insert<list<const char*>>(data);
    }

    {
        auto duration = run_insert<vector<const char*>>(data);
    }

    {
        auto duration = run_insert<set<const char*>>(data);
    }

    {
        auto duration = run_remove<list<const char*>>(data);
    }

    {
        auto duration = run_remove<vector<const char*>>(data);
    }

    {
        auto duration = run_remove<set<const char*>>(data);
    }
}
