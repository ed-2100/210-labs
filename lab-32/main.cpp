#include <chrono>
#include <deque>
#include <print>

#include "Car.h"

using namespace std;

constexpr size_t INITIAL_SIZE = 2;

int main() {
    srand(chrono::steady_clock::now().time_since_epoch().count());

    deque<Car> line;

    for (size_t i = 0; i < INITIAL_SIZE; i++) {
        line.push_back(Car());
    }

    println("Initial Queue:");
    for (Car& car : line) {
        print("    ");
        car.print();
    }
    
    return EXIT_SUCCESS;
}
