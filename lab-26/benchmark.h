// COMSC-210 | Lab 26 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#include <chrono>
#include <span>
#include <optional>
#include <string>

using namespace std;

using Duration = chrono::high_resolution_clock::duration;
using Result = optional<Duration>;

// Simple wrapper for measuring the execution time of an operation.
//
// ### Arguments
//
// - `f`; The function whose execution time is to be measured.
template <typename F>
Duration measure(F f) {
    auto begin = chrono::high_resolution_clock::now();
    f();
    auto end = chrono::high_resolution_clock::now();
    return end - begin;
}

// Populates a container with the provided data.
//
// ### Arguments
//
//  - `cont`: The container to populate.
//  - `data`: The data to populate the container with.
template <typename Cont>
void populate(Cont& cont, span<const string> data) {
    if constexpr ( requires { cont.reserve(data.size()); } ) {
        cont.reserve(data.size());
    }

    for (const string& s : data) {
        if constexpr ( requires {cont.push_back(s.c_str());} ) {
            // List / Vector
            cont.push_back(s.c_str());
        } else if constexpr ( requires { cont.insert(s.c_str()); } ) {
            // Set
            cont.insert(s.c_str());
        } else {
            static_assert(false, "That ain't it.");
        }
    }
}

// The `Populate` operation.
//
// Benchmarks populating a container.
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

// The `Sort` operation.
//
// Benchmarks a container's sorting function, if present.
struct Sort {
    static constexpr const char* name = "SORTING";

    template<typename Cont>
    static Result run(span<const string> data) {
        Cont cont;

        if constexpr ( requires { cont.sort(); } ) {
            // List
            populate(cont, data);
            return measure([&]() {
                cont.sort();
            });
        } else if constexpr ( requires { ranges::sort(cont); } ) {
            // Vector
            populate(cont, data);
            return measure([&]() {
                ranges::sort(cont);
            });
        } else {
            // Set
            return nullopt;
        }
    }
};

// The `Insert` operation.
//
// Benchmarks adding an item to a container.
struct Insert {
    static constexpr const char* name = "INSERTING";

    template<typename Cont>
    static Result run(span<const string> data) {
        constexpr const char item[] = "TESTCODE";

        Cont cont;
        populate(cont, data);
        if constexpr ( requires { cont.reserve(data.size() + 1); } ) {
            cont.reserve(data.size() + 1);
        }

        if constexpr ( requires { cont.insert(item); }) {
            // Set
            return measure([&]() {
                cont.insert(item);
            });
        } else {
            // List, Vector
            auto it = next(cont.begin(), cont.size() / 2);
            return measure([&]() {
                cont.insert(it, item);
            });
        }
    }
};

// The `Remove` operation.
//
// Benchmarks a container's removal operation.
struct Remove {
    static constexpr const char* name = "REMOVING";

    template<typename Cont>
    static Result run(span<const string> data) {
        Cont cont;
        populate(cont, data);
        auto it = next(cont.begin(), cont.size() / 2);
        return measure([&]() {
            cont.erase(it);
        });
    }
};

// The `Container` struct.
//
// Serves as a way to convey information about a type
// to the `benchmark` function.
template <typename Cont>
struct Container {
    using type = Cont;

    const char* name;
};

// Benchmarks a list of different containers using the provided string data
// and displays the results to `stdout`.
//
// Note: This took ages...
//
// ### Arguments
//
//  - `data`:    The data to be used when benchmarking each operation.
//  - `...cont`: An arbitrary number of `Containers` to be benchmarked.
template <typename ...Op, typename ...Cont>
void benchmark(span<const string> data, Container<Cont> ... cont) {
    auto run_item = [&]<typename O, typename C>(O, C) -> optional<array<Result, 15>> {
        array<Duration, 15> temp = {};

        for (Duration& sample : temp) {
            if (auto t = O::template run<C>(data)) {
                sample = *t;
            } else {
                return nullopt;
            }
        }

        return  temp;
    };

    auto run_row = [&]<typename O>(O) -> array<Result, sizeof...(Cont)> {
        // Expand over ...Cont
        return array{ run_item.template operator()<O, Cont>()... };
    };

    array<array<optional<array<Duration, 15>>, sizeof...(Cont)>, sizeof...(Op)> results {
        // Expand over ...Op
        run_row.template operator()<Op>()...
    };

    // Header column
    cout << "| " << setw(15) << ' ' << " |";
    ((cout << setw(15) << cont.name << " |"), ...);
    cout << "\n";

    array names { Op::name... };
    
    // Rows
    for (const auto& [name, row] : views::zip(names, results)) {
        cout << "| " << setw(15) << name << " |";
        for (const Result& result : row) {
            cout << setw(12) << result.transform(
                [](const Duration& d) {
                    return std::chrono::nanoseconds(d).count();
                }
            ).value_or(-1) << " ns |";
        }

        cout << '\n';
    }
}
