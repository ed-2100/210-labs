#pragma once

#include <iostream>
#include <cstdint>
#include <utility>
#include <string>

// The `Goat` class.
//
// Holds information on a goat.
class Goat {
    uint32_t age;
    std::string name;
    std::string color;
    static const char* const names[15];
    static const char* const colors[15];

public:
    Goat();
    Goat(uint32_t age, std::string name, std::string color);

    Goat(const Goat& rhs) : age(rhs.age), name(rhs.name), color(rhs.color) {}
    Goat(Goat&& rhs) :
        age(std::exchange(rhs.age, 0)),
        name(std::exchange(rhs.name, std::string{})),
        color(std::exchange(rhs.color, std::string{})) {}

    Goat& operator=(const Goat& rhs);
    Goat& operator=(Goat&& rhs);

    bool operator!=(const Goat& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Goat& value);
};

std::ostream& operator<<(std::ostream& os, const Goat& value);
