// System of linear equations solver, limited to 5x5 A matrices.

// Given Ax = b, solve for x.

#include <array>
#include <iostream>

using namespace std;

constexpr size_t DIM = 5;

void rref(array<array<float, DIM + 1>, DIM>& aug);
void print_array(const array<array<float, DIM + 1>, DIM>& aug);

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

    print_array(aug);

    cout << "\n\n";

    rref(aug);
    print_array(aug);
}

void rref(array<array<float, DIM + 1>, DIM>& aug) {
    for (size_t i = 0; i < DIM; i++) {
        float rcp = 1.0 / aug[i][i];

        for (size_t c = i; c < DIM + 1; c++) {
            aug[i][c] *= rcp;
        }

        for (size_t r = i + 1; r < DIM; r++) {
            float k = aug[r][i];

            for (size_t c = i; c < DIM + 1; c++) {
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

        cout << row[0];

        for (size_t i = 1; i < row.size(); i++) {
            cout << ' ' << row[i];
        }

        cout << '\n';
    }
}
