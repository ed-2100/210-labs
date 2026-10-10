#pragma once

#include <iostream>
#include <cstdint>
#include <utility>

class Goat {
    uint32_t age;
    string name;
    string color;

    const char* const names[15] = {
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

    const char* const colors[15] = {
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

public:
    Goat();

    Goat(uint32_t age, string name, string color);

    Goat(const Goat& rhs) : age(rhs.age), name(rhs.name), color(rhs.color) {}
    Goat(Goat&& rhs) :
        age(std::exchange(rhs.age, 0)),
        name(std::exchange(rhs.name, string{})),
        color(std::exchange(rhs.color, string{})) {}

    Goat& operator=(const Goat& rhs);
    Goat& operator=(Goat&& rhs);

    bool operator!=(const Goat& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Goat& value);
};

std::ostream& operator<<(std::ostream& os, const Goat& value);
