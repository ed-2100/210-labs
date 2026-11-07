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

    size_t time = 1;

    uniform_int_distribution<> dist_probability(0, 99);

    while (!line.empty()) {
        print("Time: {} Operation: ", time);

        if (dist_probability(gen) < 55) {
            // Pay Toll
            line.push_back(Car());
            print("Joined lane: ");
            line.back().print();
        } else {
            // Join Line
            Car car = move(line.front());
            line.pop_front();
            print("Car paid: ");
            car.print();
        }

        println("Queue:");
        if (line.empty()) {
        }
            for (Car& car : line) {
                print("    ");
                car.print();
            }
        }

        println();

        time += 1;
    }
    
    return EXIT_SUCCESS;
}
