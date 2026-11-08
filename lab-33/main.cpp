// COMSC-210 | Lab 33 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#include <chrono>
#include <cstddef>
#include <deque>
#include <print>
#include <random>
#include <ranges>

#include "Car.h"

using namespace std;

constexpr size_t INITIAL_SIZE = 2;
constexpr size_t N_ITERATIONS = 20;
constexpr size_t PAY_P = 46;
constexpr size_t JOIN_P = 39;
constexpr size_t SWITCH_P = 15;

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
        for (size_t i : views::iota(
            static_cast<decltype(INITIAL_SIZE)>(0), 
            INITIAL_SIZE
        )) {
            lane.push_back(Car());
        }
    }

    println("Initial queue:");
    for (auto [i, lane] : lanes | views::enumerate) {
        println("Lane {}", i + 1);
        for (Car& car : lane) {
            print("    ");
            car.print();
        }
    }

    uniform_int_distribution dist_empty(0, 1);
    discrete_distribution dist_p({PAY_P, JOIN_P, SWITCH_P});
    uniform_int_distribution dist_lane(1, 3);

    for (size_t time : views::iota(
        static_cast<decltype(N_ITERATIONS)>(0),
        N_ITERATIONS
    )) {
        println("\nTime: {}", time + 1);

        for (auto [i, lane] : lanes | views::enumerate) {
            print("Lane: {} ", i + 1);

            switch (lane.empty() ? dist_empty(gen) : dist_p(gen)) {
                case 0: {
                    // Pay Toll
                    if (lane.empty()) {
                        println("no operation");
                        break;
                    }
                    Car car = move(lane.front());
                    lane.pop_front();
                    print("Paid: ");
                    car.print();
                    break;
                }
                case 1: {
                    // Join Lane
                    lane.push_back(Car());
                    print("Joined: ");
                    lane.back().print();
                    break;
                }
                case 2: {
                    // Switch Lanes
                    size_t new_lane = (i + dist_lane(gen)) % lanes.size();
                    lanes[new_lane].push_back(move(lane.back()));
                    lane.pop_back();
                    print("Switched: ");
                    lanes[new_lane].back().print();
                    break;
                }
            }
        }

        for (auto [i, lane] : lanes | views::enumerate) {
            print("Lane {} Queue:", i + 1);
            if (lane.empty()) {
                println(" empty");
            } else {
                println();
                for (Car& car : lane) {
                    print("\t");
                    car.print();
                }
            }
        }
    }
    
    return EXIT_SUCCESS; // :)
}
