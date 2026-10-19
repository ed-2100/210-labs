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

using namespace std;

using Duration = chrono::high_resolution_clock::duration;
using Result = optional<Duration>;

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
    static constexpr const char* name = "READING";

    template<typename Cont>
    static Result run(span<const string> data) {
        Cont cont;
        return measure([&]() {
            populate(cont, data);
        });
    }
};

struct Sort {
    static constexpr const char* name = "SORTING";

    template<typename Cont>
    static Result run(span<const string> data) {
        Cont cont;

        if constexpr ( requires { cont.sort(); } ) {
            populate(cont, data);
            return measure([&]() {
                cont.sort();
            });
        } else if constexpr ( requires { ranges::sort(cont); } ) {
            populate(cont, data);
            return measure([&]() {
                ranges::sort(cont);
            });
        } else {
            return nullopt;
        }
    }
};

struct Insert {
    static constexpr const char* name = "INSERTING";

    template<typename Cont>
    static Result run(span<const string> data) {
        Cont cont;
        populate(cont, data);
        return measure([&]() {
            auto it = next(cont.begin(), (cont.size() >> 1) - 1);
            cont.insert(it, "TESTCODE");
        });
    }
};

struct Remove {
    static constexpr const char* name = "REMOVING";

    template<typename Cont>
    static Result run(span<const string> data) {
        Cont cont;
        populate(cont, data);
        return measure([&]() {
            auto it = next(cont.begin(), (cont.size() >> 1) - 1);
            cont.erase(it);
        });
    }
};

template <typename Cont>
struct Container {
    using type = Cont;

    const char* name;
};

template <typename ...Op, typename ...Cont>
void benchmark(span<const string> data, Container<Cont> ... cont) {
    auto run_row = [&]<typename O>(O) -> array<Result, sizeof...(Cont)> {
        return array{ O::template run<Cont>(data)... };
    };

    array<array<Result, sizeof...(Cont)>, sizeof...(Op)> results {
        run_row(Op{})...
    };

    

    for (const auto& row : results) {

        cout << "| ";
        for (const Result& result : row) {
            cout << setw(15) << result.transform(
                [](const Duration& d) {
                    return std::chrono::nanoseconds(d).count();
                }
            ).value_or(-1) << " |";
        }

        cout << '\n';
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
}
