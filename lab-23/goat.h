#pragma once

#include <iostream>
#include <utility>

using namespace std;

class Goat {
private:
    string name;
    int age;
    string color;
public:
    Goat(string name = "", int age = 0, string color = "") {
        this->name = std::move(name);
        this->age = age;
        this->color = std::move(color);
    }

    // Goat(Goat& rhs) : name(rhs.name), age(rhs.age), color(rhs.color) {}
    // Goat(Goat&& rhs)
    //   : name(std::exchange(rhs.name, "")),
    //     age(std::exchange(rhs.age, 0)),
    //     color(std::exchange(rhs.color, "")) {}

    // Goat& operator=(const Goat& rhs) {
    //     if (this != &rhs) {
    //         this->name = rhs.name;
    //         this->age = rhs.age;
    //         this->color = rhs.color;
    //     }
    //     return *this;
    // }

    // Goat& operator=(Goat&& rhs) {
    //     if (this != &rhs) {

    //     }
    // }

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
};
