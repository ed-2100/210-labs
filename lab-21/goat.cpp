#include <random>
#include <format>
#include <chrono>

#include "goat.h"

using namespace std;

const char* const Goat::names[15] = {
    "William",
    "John",
    "Thomas",
    "George",
    "Henry",
    "Charles",
    "James",
    "Edward",
    "Frederick",
    "Arthur",
    "Mary",
    "Elizabeth",
    "Sarah",
    "Jane",
    "Emma"
};

const char* const Goat::colors[15] = {
    "Black",
    "White",
    "Red",
    "Blue",
    "Green",
    "Yellow",
    "Brown",
    "Gray",
    "Silver",
    "Maroon",
    "Green",
    "Olive",
    "Navy",
    "Teal",
    "Orange"
};

Goat::Goat() {
    auto current_time = chrono::steady_clock::now();

    mt19937 gen(current_time.time_since_epoch().count());

    uniform_int_distribution<uint32_t> dist_age(1, 20);
    uniform_int_distribution<uint32_t> dist_idx(0, 14);

    age = dist_age(gen);
    name = names[dist_idx(gen)];
    color = colors[dist_idx(gen)];
}

Goat::Goat(uint32_t age, string name, string color) {
    this->age = age;
    this->name = move(name);
    this->color = move(color);
}


Goat& Goat::operator=(const Goat& rhs) {
    if (this != &rhs) {
        age = rhs.age;
        name = rhs.name;
        color = rhs.color;
    }
    return *this;
}

Goat& Goat::operator=(Goat&& rhs) {
    if (this != &rhs) {
        age = exchange(rhs.age, 0);
        name = exchange(rhs.name, string{});
        color = exchange(rhs.color, string{});
    }
    return *this;
}

bool Goat::operator!=(const Goat& rhs) {
    return age != rhs.age || name != rhs.name || color != rhs.color;
}

std::ostream& operator<<(std::ostream& os, const Goat& value) {
    return os << format("{} ({}, {})", value.name, value.color, value.age);
}
