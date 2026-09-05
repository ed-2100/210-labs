#include <cstdint>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <vector>
#include <random>

using namespace std;

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

// Prints a table of `Color`s to `f`.
//
// Arguments:
//
// - `f`: The `ostream` to print to
// - `colors`: The array of color values
// - `n_colors`: The length of `colors`
void print_colors(ostream& f, const Color *colors, size_t n_colors);

int main() {
    vector<Color> test_vec;

    mt19937 gen(42);
    uniform_int_distribution<size_t> dist_n_color(25, 50);
    uniform_int_distribution<uint32_t> dist_value(0, 255);

    size_t n_color = dist_n_color(gen);

    test_vec.reserve(test_vec.size() + n_color);

    for (size_t i = 0; i < n_color; i++) {
        test_vec.push_back(Color {
            .red   = static_cast<uint8_t>(dist_value(gen)),
            .green = static_cast<uint8_t>(dist_value(gen)),
            .blue  = static_cast<uint8_t>(dist_value(gen)),
        });
    }

    print_colors(cout, test_vec.data(), test_vec.size());

    return 0;
}

void print_colors(ostream& f, const Color *colors, size_t n_colors) {
    f << "Color #   R value   G value   B value\n"
      << "-------   -------   -------   -------\n";
    
    for (size_t i = 0; i < n_colors; i++) {
        const Color& color = colors[i];

        f <<      "  " << setw(3) << i + 1
          << "       " << setw(3) << static_cast<int>(color.red)
          << "       " << setw(3) << static_cast<int>(color.green)
          << "       " << setw(3) << static_cast<int>(color.blue)
          << "\n";
    }
}
