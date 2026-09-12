#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <unistd.h>

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

bool enterArrayData(double* arr, size_t n_arr, bool retry_on_fail) {
    cout << "Data entry for the array:\n";

    for (size_t i = 0; i < n_arr; i++) {
        cout << "    > Element #" << i << ": ";
        
        if (!(cin >> arr[i])) {
            cerr << "Invalid number!";
            break;
        }
    }

    cout << "Data entry complete.";
}


void outputArrayData(double* arr, size_t n_arr) {
    cout << "Outputting array elements: ";
    for (size_t i = 0)
}

double sumArray() {

}
