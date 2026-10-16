#pragma once

#include <iostream>

using namespace std;

class Goat {
private:
    string name;
    int age;
    string color;
public:
    Goat(string name = "", int age = 0, string color = "") {
        this->name = name;
        this->age = age;
        this->color = color;
    }

    template<typename String>
    void set_name(String&& n) {
        name = forward<String>(n);
    };

    template<typename Int>
    void set_age(Int&& a) {
        age = forward<Int>(a);
    };

    template<typename String>
    void set_color(String&& c) {
        color = forward<String>(c);
    }

    const string& get_name() const {
        return name;
    };

    int get_age() const {
        return age;
    }

    const string& get_color() const {
        return color;
    }
};
