// COMSC-210 | Lab 14 | Edwin Burwell
//
// Note: This code may contain features from newer C++ versions, such as C++23.

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <format>
#include <vector>
#include <random>

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
    // Default, full, and partial constructor.
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
    void print();
};

// The main function.
//
// Instantiates multiple `Color` objects with random data
// and calls each object's `print()` method.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main() {
    vector<Color> colors;

    mt19937 gen(42);
    uniform_int_distribution<uint32_t> dist_value(0, 255);

    size_t n_color = 10;

    colors.reserve(colors.size() + n_color);

    for (size_t i = 0; i < n_color; i++) {
        Color color;

        cout << format("Initializing object {} with ")
        switch (i % 3) {
            case 0:
                cout << format(
                    "default constructor...\n",
                    i + 1
                );
                color = Color();
                break;
            case 1:
                cout << format(
                    "Initializing object {} with full constructor...\n",
                    i + 1
                );
                break;
            case 2:
                break;
        }

        // color.set_r(static_cast<uint8_t>(dist_value(gen)));
        // color.set_g(static_cast<uint8_t>(dist_value(gen)));
        // color.set_b(static_cast<uint8_t>(dist_value(gen)));

        colors.push_back(move(color));
    }

    cout << format("List of {} colors:\n", n_color);

    for (size_t i = 0; i < colors.size(); i++) {
        cout << i + 1 << ": ";
        colors[i].print();
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

void Color::print() {
    cout << format("({}, {}, {})", m_r, m_g, m_b);
}
