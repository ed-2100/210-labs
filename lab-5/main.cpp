#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

// TODO: add function declarations
bool enterArrayData(double* arr, size_t n_arr);
void outputArrayData(double* arr, size_t n_arr);
double sumArray(double* arr, size_t n_arr);

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
