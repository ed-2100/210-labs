// COMSC-210 | Lab 33 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#include <chrono>
#include <deque>
#include <numeric>
#include <print>
#include <random>
#include <ranges>

#include "Car.h"

using namespace std;

constexpr size_t INITIAL_SIZE = 2;

// The `main` function.
//
// Demonstrates the standard library `deque` class using a
// traffic toll scenario.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main() {
    auto seed = chrono::steady_clock::now().time_since_epoch().count();
    srand(seed);
    mt19937 gen(seed);

    array<deque<Car>, 4> lanes;

    for (deque<Car>& lane : lanes) {
        for (size_t i : views::iota(0, 4)) {
            lane.push_back(Car());
        }
    }

    println("Initial Queue:");
    for (auto [i, lane] : lanes | views::enumerate) {
        println("Lane {}", i + 1);
        for (Car& car : lane) {
            print("    ");
            car.print();
        }
    }

    size_t time = 1;

    uniform_int_distribution<> dist_probability(0, 99);

    while (!lanes.empty()) {
        println("\nTime: {}", time);

        for (auto [i, lane] : lanes | views::enumerate) {
            print("Lane: {} ", i + 1);

            if (dist_probability(gen) < 45) {
                // Join Line
                lane.push_back(Car());
                print("Joined: ");
                lane.back().print();
            } else {
                // Pay Toll
                Car car = move(lane.front());
                lane.pop_front();
                print("Paid: ");
                car.print();
            }
        }

        for (auto [i, lane] : lanes | views::enumerate) {
            println("Lane {} Queue:", i + 1);
            if (lanes.empty()) {
                println("    Empty");
            } else {
                for (Car& car : lane) {
                    print("    ");
                    car.print();
                }
            }
        }

        time += 1;
    }
    
    return EXIT_SUCCESS; // :)
}
