// System of linear equations solver, limited to 5x5 A matrices.

// Given Ax = b, solve for x.

#include <array>
#include <iostream>

using namespace std;

constexpr int DIM = 5;

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

}
