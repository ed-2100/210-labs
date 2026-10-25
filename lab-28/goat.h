// COMSC-210 | Lab 28 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#pragma once

#include <iostream>

using namespace std;

const int MAX_AGE = 20;

class Goat {
private:
    string name;
    int age;
    string color;
public: 
    Goat(string n = "", int a = 0, string c = "") : name(n), age(a), color(c) {}
    
    void set_name(string n) {
        name = n;
    };
    string get_name() const {
        return name; };
    void set_age(int a) {
        age = a; };
    int get_age() const {
        return age; }
    void set_color(string c) {
        color = c; }
    string get_color() const {
        return color; }

    bool operator< (const Goat &other) const {
        return name < other.name;
    }
};

// The `Goat` class.
//
// Holds information on a goat.
class Goat {
private:
    string name;
    int age;
    string color;
public:
    Goat(string name = "", int age = 0, string color = "") : name() {
        this->name = std::move(name);
        this->age = age;
        this->color = std::move(color);
    }

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
