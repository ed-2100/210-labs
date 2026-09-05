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

void print_color_table(ostream f, const Color *colors, size_t n_colors);
void print_color_row(ostream f, const Color &color);

void print_color_table(ostream f, const Color *colors, size_t n_colors) {
    f << "| Color # | R value | G value | B value |\n"
      << "| ------- | ------- | ------- | ------- |\n";
    
    for (size_t i = 0; i < n_colors; i++) {
        const Color& color = colors[i];

        f << "|   " << setw(3) << i << "   |   " << setw(3) << color.red ;
    }
}

void print_color_row(ostream f, const Color &color) {

}

int main() {
    

    return 0;
}



