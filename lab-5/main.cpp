#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

// Parses numbers from `stdin` and populates `arr`.
//
// ### Arguments
//
// - `arr`: The array to be initialized
// - `n_arr`: The length of `arr`
//
// ### Returns
//
// A boolean value that is true on success.
bool enterArrayData(double* arr, size_t n_arr);

// Prints a formatted array to `stdout`.
//
// ### Arguments
//
// - `arr`: The array to be printed
// - `n_arr`: The length of `arr`
//
// ### Returns
//
// A boolean value that is true on success.
void outputArrayData(double* arr, size_t n_arr);

// Calculates the sum of all elements in an array.
//
// ### Arguments
//
// - `arr`: The array to be summed
// - `n_arr`: The length of `arr`
//
// ### Returns
//
// The sum of all elements in the array.
double sumArray(double* arr, size_t n_arr);

// The main function.
//
// Takes user input, prints it, sums it, and prints
// it again, per assignment guidelines.
//
// ### Arguments
//
// - None
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main() {
    vector<double> arr;
    arr.resize(5);

    if (!enterArrayData(arr.data(), arr.size())) {
        cerr << "Failed to properly parse input!";
        return EXIT_FAILURE;
    }

    outputArrayData(arr.data(), arr.size());

    cout << "Sum of values: " << sumArray(arr.data(), arr.size()) << '\n';

    return EXIT_SUCCESS;
}

bool enterArrayData(double* arr, size_t n_arr) {
    cout << "Data entry for the array:\n";

    for (size_t i = 0; i < n_arr; i++) {
        cout << "    > Element #" << i << ": ";
        
        if (!(cin >> arr[i])) {
            cerr << "Invalid number!";
            return false;
        }
    }

    cout << "Data entry complete.\n";

    return true;
}

void outputArrayData(double* arr, size_t n_arr) {
    cout << "Outputting array elements: ";
    
    for (size_t i = 0; i < n_arr; i++) {
        cout << arr[i] << ' ';
    }

    cout << '\n';
}

double sumArray(double* arr, size_t n_arr) {
    double sum = 0;

    for (size_t i = 0; i < n_arr; i++) {
        sum += arr[i];
    }

    return sum;
}
