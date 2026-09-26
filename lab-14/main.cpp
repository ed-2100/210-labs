#include <cstdlib>
#include <cstdint>
#include <iostream>

using namespace std;

class Color {
private:
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;

public:
    uint8_t get_r();
    uint8_t get_g();
    uint8_t get_b();

    void set_r(uint8_t value);
    void set_g(uint8_t value);
    void set_b(uint8_t value);

    void print() {
        cout << "("  << m_r
             << ", " << m_g
             << ", " << m_b
             << ")";
    }
};

int main() {
    Color {}

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
