#include <chrono>
#include <deque>
#include <print>
#include <random>

#include "Car.h"

using namespace std;

constexpr size_t INITIAL_SIZE = 2;

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

    size_t time = 0;

    uniform_int_distribution<> dist_probability(0, 99);

    while (!line.empty()) {

        bool 
    }
    
    return EXIT_SUCCESS;
}
