// System of linear equations solver, limited to 5x5 A matrices.

// Given Ax = b, solve for x.

#include <array>
#include <iostream>

using namespace std;

constexpr size_t DIM = 5;

int main() {
    array<array<float, DIM>, DIM> A;
    array<float, DIM> b;
    array<array<float, DIM + 1>, DIM> aug = {
        array<float, DIM + 1>
        { 1,  2,  3,  4,  5,  6},
        { 3,  4,  5,  6,  7,  8},
        { 5,  6,  7,  8,  9, 10},
        { 7,  8,  9, 10, 11, 12},
        {11, 12, 13, 14, 15, 16}
    };
}

void rref(array<array<float, DIM + 1>, DIM>& aug) {
    array<float, DIM + 1> row;

    for (size_t i = 0; i < DIM - 1; i++) {
        float rcp = 1.0 / aug[i][i];

        for (size_t c = i; c < DIM + 1; c++) {
            aug[i][c] *= rcp;
        }

        for (size_t r = 0; r < DIM; r++) {
            if (r == i) {
                continue;
            }

            float k = aug[r][i];

            for (size_t c = i; c < DIM + 1; c++) {
                aug[r][c] -= aug[i][c] * k;
            }
        }
    }
}

void print_array(const array<array<float, DIM + 1>, DIM>& aug) {
    for (const auto& row : aug) {
        for (const auto& item : aug)
    }
}
