// COMSC-210 | Lab 32 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#include <chrono>
#include <deque>
#include <print>
#include <random>

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

    deque<Car> line;

    for (size_t i = 0; i < INITIAL_SIZE; i++) {
        line.push_back(Car());
    }

    println("Initial Queue:");
    for (Car& car : line) {
        print("    ");
        car.print();
    }

    size_t time = 1;

    uniform_int_distribution<> dist_probability(0, 99);

    while (!line.empty()) {
        print("\nTime: {} Operation: ", time);

        if (dist_probability(gen) < 45) {
            // Join Line
            line.push_back(Car());
            print("Joined lane: ");
            line.back().print();
        } else {
            // Pay Toll
            Car car = move(line.front());
            line.pop_front();
            print("Car paid: ");
            car.print();
        }

        println("Queue:");
        if (line.empty()) {
            println("    Empty");
        } else {
            for (Car& car : line) {
                print("    ");
                car.print();
            }
        }

        time += 1;
    }
    
    return EXIT_SUCCESS; // :)
}
