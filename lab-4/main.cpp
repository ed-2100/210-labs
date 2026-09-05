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

void print_color_table(ostream f, const const Color colors[]);
void print_color_row(ostream f, const Color &color);

void print_color_table(ostream f, const const Color colors[]) {
    f << "| Color # | R value | G value | B value |\n"
      << "| ------- | ------- | ------- | ------- |\n";
    
    for (const auto &color : colors) {
        
    }
}

void print_color_row(ostream f, const Color &color) {
      << "|   " << setw(3) << color << "   |   " << setw(3) << ;

}

int main() {
    

    return 0;
}



