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

constexpr size_t INITIAL_SIZE = 2, PAY_P = 46, JOIN_P = 39, SWITCH_P = 15;

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
        for (size_t i : views::iota(static_cast<size_t>(0), INITIAL_SIZE)) {
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

    discrete_distribution dist_probability({PAY_P, JOIN_P, SWITCH_P});
    uniform_int_distribution dist_lane(1, 3);

    for (size_t time : views::iota(0, 20)) {
        println("\nTime: {}", time);

        for (auto [i, lane] : lanes | views::enumerate) {
            print("Lane: {} ", i + 1);

            auto prob = dist_probability(gen);

            switch (dist_probability(gen)) {
                case 0: {
                    // Pay Toll
                    Car car = move(lane.front());
                    lane.pop_front();
                    print("Paid: ");
                    car.print();
                    break;
                }
                case 2: {
                    // Join Lane
                    lane.push_back(Car());
                    print("Joined: ");
                    lane.back().print();
                    break;
                }
                case 3: {
                    // Switch Lanes
                    size_t new_lane = (i + dist_lane(gen)) % lanes.size();
                    lanes[new_lane].push_back(move(lane.back()));
                    lane.pop_back();
                    print("Switched: ");
                    lanes[new_lane].back().print();
                    
                }
            }
            if (prob < PAY_P && !lane.empty())
            
            if (prob > PAY_P && prob < PAY_P + JOIN_P) {
            }
            
            if (prob > PAY_P + JOIN_P && prob < PAY_P + JOIN_P!lane.empty()) {
            } else {
                print("No Operation");
            }
        }

        for (auto [i, lane] : lanes | views::enumerate) {
            println("Lane {} Queue:", i + 1);
            if (lane.empty()) {
                println("    Empty");
            } else {
                for (Car& car : lane) {
                    print("\t");
                    car.print();
                }
            }
        }
    }
    
    return EXIT_SUCCESS; // :)
}
