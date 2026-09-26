#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <format>
#include <vector>
#include <random>

using namespace std;

class Color {
private:
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;

public:
    Color(uint8_t r, uint8_t g, uint8_t b) {
        m_r = r;
        m_g = g;
        m_b = b;
    }

    uint8_t get_r();
    uint8_t get_g();
    uint8_t get_b();

    void set_r(uint8_t value);
    void set_g(uint8_t value);
    void set_b(uint8_t value);

    void print() {
        cout << format("({}, {}, {})", m_r, m_g, m_b);
    }
};

int main() {
    vector<Color> colors;

    mt19937 gen(42);
    uniform_int_distribution<uint32_t> dist_value(0, 255);

    size_t n_color = 10;

    colors.reserve(colors.size() + n_color);

    for (size_t i = 0; i < n_color; i++) {
        colors.push_back(Color {
            static_cast<uint8_t>(dist_value(gen)),
            static_cast<uint8_t>(dist_value(gen)),
            static_cast<uint8_t>(dist_value(gen)),
        });
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
