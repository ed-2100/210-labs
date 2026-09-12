#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// TODO: add function declarations

int main() {
    size_t n_arr = 5;
    vector<double> arr;
    arr.resize(n_arr);

    if (!enterArrayData(arr.data(), arr.size())) {
        cerr << "Failed to properly parse input!";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

bool enterArrayData(double* arr, size_t n_arr) {
    cout << "Data entry for the array:\n";

    for 
}

void outputArrayData(double* arr, size_t n_arr) {

}

double sumArray() {

}
