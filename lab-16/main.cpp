// COMSC-210 | Lab 14 | Edwin Burwell
//
// Note: This code may contain features from newer C++ versions, such as C++23.

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <format>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

// The `Color` class.
//
// Holds an 8-bit RGB value.
class Color {
private:
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;

public:
    // Default, partial, and full constructor.
    //
    // ### Arguments
    //
    // - `r`: The red color channel.
    // - `g`: The green color channel.
    // - `b`: The blue color channel.
    Color(
        uint8_t r = 0,
        uint8_t g = 0,
        uint8_t b = 0
    ) : m_r(r),
        m_g(g),
        m_b(b) {}

    // ===============================
    // ===== Getters and Setters =====
    // ===============================

    uint8_t get_r();
    uint8_t get_g();
    uint8_t get_b();

    void set_r(uint8_t r);
    void set_g(uint8_t g);
    void set_b(uint8_t b);

    // =========================
    // ===== Class Methods =====
    // =========================

    // Prints the object's RGB value to `stdout`.
    void print() const;
};

// The main function.
//
// Instantiates multiple `Color` objects with random
// data using various constructors and calls each
// object's `print()` method.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main() {
    vector<tuple<Color, const char*>> colors;

    mt19937 gen(42);
    uniform_int_distribution<uint32_t> dist_value(0, 255);

    size_t n_color = 10;

    constexpr const char* MESSAGES[] = {
        "default\0",
        "1 param\0",
        "2 params\0",
        "full\0"
    };

    colors.reserve(colors.size() + n_color);

    for (size_t i = 0; i < n_color; i++) {
        Color color;
        
        switch (i % 4) {
            case 0:
                color = Color();
                break;
            case 1:
                color = Color(
                    static_cast<uint8_t>(dist_value(gen))
                );
                break;
            case 2:
                color = Color(
                    static_cast<uint8_t>(dist_value(gen)),
                    static_cast<uint8_t>(dist_value(gen))
                );
                break;
            case 3:
                color = Color(
                    static_cast<uint8_t>(dist_value(gen)),
                    static_cast<uint8_t>(dist_value(gen)),
                    static_cast<uint8_t>(dist_value(gen))
                );
                break;
        }

        colors.emplace_back(move(color), MESSAGES[i % 4]);
    }

    cout << format("List of {} colors:\n", n_color);

    for (size_t i = 0; i < colors.size(); i++) {
        const auto& [color, msg] = colors[i];

        cout << left
             << setw(4) << format("{}: ", i + 1)
             << setw(9) << msg
             << setw(15);

        color.print();

        cout << '\n';
    }

    return EXIT_SUCCESS; // :)
}


uint8_t Color::get_r() {
    return m_r;
}

uint8_t Color::get_g() {
    return m_g;
}

uint8_t Color::get_b() {
    return m_b;
}

void Color::set_r(uint8_t r) {
    m_r = r;
}

void Color::set_g(uint8_t g) {
    m_g = g;
}

void Color::set_b(uint8_t b) {
    m_b = b;
}

void Color::print() const {
    cout << format("({:>3}, {:>3}, {:>3})", m_r, m_g, m_b);
}
