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

void print_color(ostream f, const Color &color) {
    cout << "| Color # | R value | G value | B value |\n"
         << "| ------- | ------- | ------- | ------- |\n"
         << "";
}

int main() {
    

    return 0;
}



