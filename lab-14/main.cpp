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
    uint8_t m_r = 0;
    uint8_t m_g = 0;
    uint8_t m_b = 0;

public:
    uint8_t get_r();
    uint8_t get_g();
    uint8_t get_b();

    void set_r(uint8_t value);
    void set_g(uint8_t value);
    void set_b(uint8_t value);

    // Prints the object's color value to `stdout`.
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

        color.set_r(static_cast<uint8_t>(dist_value(gen)));
        color.set_g(static_cast<uint8_t>(dist_value(gen)));
        color.set_b(static_cast<uint8_t>(dist_value(gen)));

        colors.push_back(move(color));
    }

    cout << format("List of {} colors:\n", n_color);

    for (size_t i = 0; i < colors.size(); i++) {
        cout << i + 1 << ": ";
        colors[i].print();
        cout << '\n';
    }

    return EXIT_SUCCESS;
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

void Color::set_r(uint8_t value) {
    m_r = value;
}

void Color::set_g(uint8_t value) {
    m_g = value;
}

void Color::set_b(uint8_t value) {
    m_b = value;
}

void Color::print() {
    cout << format("({}, {}, {})", m_r, m_g, m_b);
}
