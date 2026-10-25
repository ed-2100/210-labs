// COMSC-210 | Lab 28 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#pragma once

#include <iostream>

using namespace std;

const int MAX_AGE = 20;

// The `Goat` class.
//
// Holds information on a goat.
class Goat {
private:
    string name;
    int age;
    string color;
public:
    template<typename String1, typename Int, typename String2>
    Goat(String1&& n = "", Int&& a = 0, String2&& c = "") :
        name(std::forward<String1>(n)),
        age(std::forward<Int>(a)),
        color(std::forward<String2>(c)) {}

    template<typename String>
    void set_name(String&& n) {
        name = forward<String>(n);
    }

    template<typename Int>
    void set_age(Int&& a) {
        age = forward<Int>(a);
    }

    template<typename String>
    void set_color(String&& c) {
        color = forward<String>(c);
    }

    const string& get_name() const {
        return name;
    }

    int get_age() const {
        return age;
    }

    const string& get_color() const {
        return color;
    }

    auto operator<=>(const Goat& rhs) const = default;
};
