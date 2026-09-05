#include <cstdint>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <vector>

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

    test_vec.push_back(Color {
        .red = 42,
        .green = 0,
        .blue = 255,
    });

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
