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
        float n1 = aug[i][i];
        float n2 = aug[i][i];

        float q = - n2 / n1;

        for (size_t j = i; j < DIM + 1; j++) {
            row[j] = aug[i][j] * q;
        }

        for (size_t r = 0; r < )
    }
}

void rmul(array<float, DIM + 1>& row, float k) {
    
}

void radd(array<float, DIM + 1>& a, const array<float, DIM + 1>& b) {
    for (size_t i = 0; i < DIM + 1; i++) {
        a[i] += b[i];
    }
}
