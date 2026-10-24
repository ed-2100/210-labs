// COMSC-210 | Lab 26 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#include <chrono>
#include <span>
#include <optional>
#include <string>

using namespace std;

constexpr size_t N_SAMPLES = 15;

using Duration = chrono::high_resolution_clock::duration;
using Result = optional<Duration>;
using DurationArray = array<Duration, N_SAMPLES>;
using Results = optional<DurationArray>;

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
        if constexpr ( requires {cont.push_back(s);} ) {
            // List / Vector
            cont.push_back(s);
        } else if constexpr ( requires { cont.insert(s); } ) {
            // Set
            cont.insert(s);
        } else {
            static_assert(false, "That ain't it.");
        }
    }
}

// The `Populate` operation.
//
// Benchmarks populating a container.
struct Populate {
    static constexpr const char* name = "Read";

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
    static constexpr const char* name = "Sort";

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
    static constexpr const char* name = "Insert";

    template<typename Cont>
    static Result run(span<const string> data) {
        string item = "TESTCODE";

        Cont cont;
        populate(cont, data);
        if constexpr ( requires { cont.reserve(data.size() + 1); } ) {
            cont.reserve(data.size() + 1);
        }

        if constexpr ( requires { cont.insert(move(item)); }) {
            // Set
            return measure([&]() {
                cont.insert(move(item));
            });
        } else {
            // List, Vector
            auto it = next(cont.begin(), cont.size() / 2);
            return measure([&]() {
                cont.insert(it, move(item));
            });
        }
    }
};

// The `Remove` operation.
//
// Benchmarks a container's removal operation.
struct Remove {
    static constexpr const char* name = "Delete";

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

// Helper function for taking multiple samples a given
// operation + container combination.
//
// ### Returns
//
// An optional array containing the duration of each sample.
//
// If the operation isn't timeable with the provided container,
// `nullopt` is returned.
template <typename O, typename C>
auto run_item(span<const string> data) -> Results {
    DurationArray temp = {};

    for (Duration& sample : temp) {
        auto result = O::template run<C>(data);

        if (!result) {
            return nullopt;
        }
        
        sample = *result;
    }

    return temp;
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
    using Row = array<Results, sizeof...(Cont)>;
    using Matrix = array<Row, sizeof...(Op)>;

    auto run_row = [&]<typename O>() -> Row {
        // Expand over ...Cont
        return array{ run_item<O, Cont>(data)... };
    };

    // A 3D array that holds the results of benchmarking each
    // operation on each container `N_SAMPLES` times;
    //
    // This variable, from outer array to inner array is:
    // operation -> container -> supports operation? -> samples
    //
    // `Matrix` expands to:
    // std::array<
    //     std::array<
    //         std::optional<std::array<
    //             Duration,
    //             N_SAMPLES>>,
    //         sizeof...(Cont)>,
    //     sizeof...(Op)
    // >
    Matrix results {
        // Expand over ...Op
        run_row.template operator()<Op>()...
    };

    cout << "Number of simulations: " << N_SAMPLES << '\n';

    // Header row
    cout << setw(10) << "Operation";
    ((cout << setw(10) << cont.name), ...);
    cout << '\n';

    array names { Op::name... };
    
    // Rows
    for (const auto& [name, row] : views::zip(names, results)) {
        cout << setw(10) << name;

        for (const Results& results : row) {
            cout << setw(10) << results.transform(
                [](const DurationArray& durations) {
                    auto sum = Duration{};

                    for (const Duration& d : durations) {
                        sum += d;
                    }
                    
                    return chrono::nanoseconds(sum / durations.size()).count();
                }
            ).value_or(-1);
        }

        cout << '\n';
    }
}
