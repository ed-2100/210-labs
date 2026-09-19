// COMSC-210 | Lab 9 | Edwin Burwell
//
// Compute the Reduced Row-Echelon form of a 4x5 matrix.

#include <array>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <filesystem>
#include <fstream>

using namespace std;

// The row reducer implementation.
//
// Converts `aug` to Reduced Row-Echelon.
//
// ### Arguments
//
// - `aug`: The matrix to be reduced, stored in row-major order.
template <const size_t NROW, const size_t NCOL>
void rref(array<float, NROW * NCOL>& aug);

// The matrix display function.
//
// Prints `aug` to `stdout`.
//
// ### Arguments
//
// - `aug`: The matrix to display, stored in row-major order.
template <const size_t NROW, const size_t NCOL>
void print_array(const array<float, NROW * NCOL>& aug);

// The matrix loader.
//
// Loads a matrix from the file specified by `path` into row-major order.
//
// ### Arguments
// 
// - `aug`: The array to load the matrix into.
template <const size_t NROW, const size_t NCOL>
void load_array(array<float, NROW * NCOL>& aug, const char* path);

// The main function.
//
// Loads an array from a file, displays it, reduces it to Reduced Row-Echelon, and displays it again.
//
// ### Arguments
//
// - `argc`: The length of `argv`.
// - `argv`: The arguments passed to the program.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main(int argc, const char** argv) {
    constexpr size_t NROW = 4;
    constexpr size_t NCOL = 5;

    array<float, NROW * NCOL> aug;

    auto file = filesystem::path(argv[0]).parent_path() / "test_sample.txt";

    load_array<NROW, NCOL>(aug, file.c_str());

    cout << "Input array:\n";

    print_array<NROW, NCOL>(aug);

    rref<NROW, NCOL>(aug);

    cout << "\n\nReduced Row-Echelon Form:\n";

    print_array<NROW, NCOL>(aug);

    cout << '\n';
}

template <const size_t NROW, const size_t NCOL>
void rref(array<float, NROW * NCOL>& aug) {
    for (size_t i = 0, j = 0; i < NROW && j < NCOL; i++, j++) {
        while (aug[i * NCOL + j] == 0) {
            size_t r = NROW - 1;

            while (aug[r * NCOL + j] == 0 && r > i) {
                r -= 1;
            }

            if (r == i) {
                j += 1;

                if (j >= NCOL) {
                    return;
                }

                continue;
            }

            for (size_t c = i; c < NCOL; c++) {
                swap(aug[i * NCOL + c], aug[r * NCOL + c]);
            }
        }

        float rcp = 1.0 / aug[i * NCOL + j];

        aug[i * NCOL + j] = 1;
        for (size_t c = j + 1; c < NCOL; c++) {
            aug[i * NCOL + c] *= rcp;
        }

        for (size_t r = 0; r < NROW; r++) {
            if (r == i) {
                continue;
            }

            float k = aug[r * NCOL + j];

            if (k == 0) {
                continue;
            }

            aug[r * NCOL + j] = 0;
            for (size_t c = j + 1; c < NCOL; c++) {
                aug[r * NCOL + c] -= aug[i * NCOL + c] * k;
            }
        }
    }
}

template <const size_t NROW, const size_t NCOL>
void print_array(const array<float, NROW * NCOL>& aug) {
    if (aug.size() == 0) {
        return;
    }

    auto print_line = [&aug](size_t r) {
        auto print_item = [&aug, &r](size_t c) {
            cout << aug[r * NCOL + c];
        };

        print_item(0);
        for (size_t c = 1; c < NCOL; c++) {
            cout << ' ';
            print_item(c);
        }
    };

    print_line(0);
    for (size_t r = 1; r < NROW; r++) {
        cout << '\n';
        print_line(r);
    }
}

template <const size_t NROW, const size_t NCOL>
void load_array(array<float, NROW * NCOL>& aug, const char* path) {
    ifstream file(path);

    size_t i = 0;

    string line;
    while (getline(file, line, '\n')) {
        stringstream line_stream(line);
        string item;
        while (getline(line_stream, item, ',')) {
            aug[i] = stof(item);

            i += 1;
        }
    }
}
