// Compute the Reduced Row-Echelon form of a 5x6 matrix.

// Given Ax = b, solve for x.

#include <array>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

constexpr size_t DIM = 5;

void rref(array<array<float, DIM + 1>, DIM>& aug);
void print_array(const array<array<float, DIM + 1>, DIM>& aug);

int main() {
    array<array<float, DIM>, DIM> A;
    array<float, DIM> b;
    array<array<float, DIM + 1>, DIM> aug = {
        array<float, DIM + 1>
        {-9, -4,  9, -9, -2,  2},
        { 0,  0, -2,  0, -2,  9},
        { 0,  3,  5,  0,  0,  9},
        { 0,  0,  0, -2,  0, -8},
        { 0,  0,  1,  0, -2, -7},
    };

    print_array(aug);
    cout << "\n\n";

    rref(aug);
    print_array(aug);
}

void rref(array<array<float, DIM + 1>, DIM>& aug) {
    for (size_t i = 0, j = 0; i < DIM && j < DIM + 1; i++, j++) {
        while (aug[i][j] == 0) {
            size_t r = DIM - 1;

            while (aug[r][j] == 0 && r > i) {
                r -= 1;
            }

            if (r == i) {
                j += 1;

                if (j >= DIM + 1) {
                    return;
                }

                continue;
            }

            for (size_t c = i; c < DIM + 1; c++) {
                swap(aug[i][c], aug[r][c]);
            }
        }

        float rcp = 1.0 / aug[i][j];

        aug[i][j] = 1;
        for (size_t c = j + 1; c < DIM + 1; c++) {
            aug[i][c] *= rcp;
        }

        for (size_t r = 0; r < DIM; r++) {
            if (r == i) {
                continue;
            }

            float k = aug[r][j];

            if (k == 0) {
                continue;
            }

            aug[r][j] = 0;
            for (size_t c = j + 1; c < DIM + 1; c++) {
                aug[r][c] -= aug[i][c] * k;
            }
        }
    }
}

void print_array(const array<array<float, DIM + 1>, DIM>& aug) {
    for (const auto& row : aug) {
        if (row.size() == 0) {
            continue;
        }

        cout << ' ' << row[0];

        for (size_t i = 1; i < row.size(); i++) {
            cout << ' ' << row[i];
        }

        cout << '\n';
    }
}
