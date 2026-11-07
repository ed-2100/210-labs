#pragma once

#include <random>
#include <print>
#include <array>

using namespace std;

constexpr int YEAR_MIN = 1990, YEAR_MAX = 2024;
constexpr int XP_MIN = 1000, XP_MAX = 9999;

class Car {
private:
    string make;
    int year;
    int transponder;

    static constexpr array manufacturers = {
        "Toyota", "Ford", "Volkswagen", "Honda", "Chevrolet", "Nissan", "BMW", 
        "Mercedes-Benz", "Audi", "Hyundai", "Kia", "Subaru", "Mazda", "Tesla", 
        "Jaguar", "Fiat", "Land Rover", "Mitsubishi", "Peugeot", "Renault", 
        "Porsche", "Lexus", "Volvo", "Skoda", "Infiniti"
    };

public:
    Car() = delete;

    template <typename Gen>
    Car(Gen& gen) {
        uniform_int_distribution<size_t> dist_mfg(0, manufacturers.size() - 1);
        uniform_int_distribution<int> dist_year(YEAR_MIN, YEAR_MAX);
        uniform_int_distribution<int> dist_transponder(XP_MIN, XP_MAX);

        make = manufacturers[dist_mfg(gen)];
        year = dist_year(gen);
        transponder = dist_transponder(gen);
    }

    const string& getMake() const {
        return make;
    }

    int getYear() const {
        return year;
    }

    int getTransponder() const {
        return transponder;
    }

    template <typename String>
    void setMake(String&& mk) {
        make = forward<String>(mk);
    }

    void setYear(int yr) {
        year = yr;
    }

    void setTransponder(int t) {
        transponder = t;
    }

    void print() const {
        println("[{} {} ({})]", year, make, transponder);
    }
};
