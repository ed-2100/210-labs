#pragma once

#include <chrono>
#include <iostream>
#include <random>

using namespace std;

const int YEAR_MIN = 1990, YEAR_MAX = 2024;
const int XP_MIN = 1000, XP_MAX = 9999;
const size_t NR_MANUFACTURERS = 25;

class Car {
private:
    string make;
    int year;
    int transponder;
    string manufacturers[NR_MANUFACTURERS] = {
        "Toyota", "Ford", "Volkswagen", "Honda", "Chevrolet", "Nissan", "BMW", 
        "Mercedes-Benz", "Audi", "Hyundai", "Kia", "Subaru", "Mazda", "Tesla", 
        "Jaguar", "Fiat", "Land Rover", "Mitsubishi", "Peugeot", "Renault", 
        "Porsche", "Lexus", "Volvo", "Skoda", "Infiniti"
    };

public:
    Car() {
        auto current = std::chrono::steady_clock::now();
        mt19937 gen(current.time_since_epoch().count());
        uniform_int_distribution<size_t> dist_mfg(0, NR_MANUFACTURERS);
        uniform_int_distribution<int> dist_year(YEAR_MIN, YEAR_MAX);
        uniform_int_distribution<int> dist_transponder(XP_MIN, XP_MAX);

        make = manufacturers[dist_mfg(gen)];
        year = dist_year(gen);
        transponder = rand() % (XP_MAX - XP_MIN + 1) + XP_MIN;
    }

    const string& getMake() {
        return make;
    }

    int getYear() {
        return year;
    }

    int getTransponder() {
        return transponder;
    }

    template <typename String>
    void setMake(string mk) {
        make = mk;
    }

    void setYear(int yr) {
        year = yr;
    }

    void setTransponder(int t) {
        transponder = t;
    }

    void print() {
        cout << "[" << year << " " << make << " (" << transponder << ")]\n";
    }

};
