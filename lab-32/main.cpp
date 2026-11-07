#include <chrono>
#include <deque>
#include <random>
#include <print>

#include "Car.h"

using namespace std;

constexpr size_t INITIAL_SIZE = 2;

int main() {
    auto current = chrono::steady_clock::now();
    mt19937 gen(current.time_since_epoch().count());

    deque<Car> line;

    for (size_t i = 0; i < INITIAL_SIZE; i++) {
        line.push_back(Car(gen));
    }

    println("Initial Queue:");
    for (const Car& car : line) {
        print("    ");
        car.print();
    }
    
    return EXIT_SUCCESS;
}
