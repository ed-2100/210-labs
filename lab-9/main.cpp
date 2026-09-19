// Compute the Reduced Row-Echelon form of a 5x6 matrix.

// Given Ax = b, solve for x.

#include <array>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <filesystem>
#include <fstream>

using namespace std;

constexpr size_t NROW = 5;
constexpr size_t NCOL = 6;

void rref(array<float, NROW * NCOL>& aug);
void print_array(const array<float, NROW * NCOL>& aug);
void load_array(array<float, NROW * NCOL>& aug, const char* path);

int main(int argc, const char** argv) {
    array<float, NROW * NCOL> aug;

    auto file = filesystem::path(argv[0]).parent_path() / "test_sample.txt";

    load_array(aug, file.c_str());

    print_array(aug);
    cout << "\n\n";

    rref(aug);
    print_array(aug);
}

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

void print_array(const array<float, NROW * NCOL>& aug) {
    if (aug.size() == 0) {
        return;
    }

    for (size_t r = 0; r < NROW; r++) {
        cout << ' ' << aug[r * NCOL];

        for (size_t c = 1; c < NCOL; c++) {
            cout << ' ' << aug[r * NCOL + c];
        }

        cout << '\n';
    }
}

void load_array(array<float, NROW * NCOL>& aug, const char* path) {
    ifstream file(path);

    size_t i = 0;

    string line;
    while (getline(file, line, '\n')) {
        if (line.empty()) {
            break;
        }

        stringstream line_stream(line);

        string item;
        while (getline(line_stream, item, ',')) {
            if (item.empty()) {
                break;
            }

            cout << item << '\n';

            aug[i] = stof(item);

            i += 1;
        }

        cout << '\n';
    }
}
