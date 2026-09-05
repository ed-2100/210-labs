#include <cstdint>
#include <iostream>
#include <ostream>
#include <iomanip>

using namespace std;

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

void print_colors(ostream& f, const Color *colors, size_t n_colors);

void print_colors(ostream& f, const Color *colors, size_t n_colors) {
    f << "| Color # | R value | G value | B value |\n"
      << "| ------- | ------- | ------- | ------- |\n";
    
    for (size_t i = 0; i < n_colors; i++) {
        const Color& color = colors[i];

        f <<    "|   " << setw(3) << i + 1
          << "   |   " << setw(3) << static_cast<int>(color.red)
          << "   |   " << setw(3) << static_cast<int>(color.green)
          << "   |   " << setw(3) << static_cast<int>(color.blue)
          << "   |\n";
    }
}

int main() {
    Color test_color = {
        .red = 42,
        .green = 0,
        .blue = 255,
    };

    print_colors(cout, &test_color, 1);

    return 0;
}



