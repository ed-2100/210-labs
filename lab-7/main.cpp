#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Reverses an array of `string`s in-place.
//
// ### Arguments
//
// - `arr`: The array to be reversed
// - `n_arr`: The length of `arr`
void reverseArray(string* arr, size_t n_arr);

// Prints an array of `string`s `stdout`, separated by spaces.
//
// ### Arguments
//
// - `arr`: The array to be printed
// - `n_arr`: The length of `arr`
void displayArray(string* arr, size_t n_arr);

// The main function.
//
// Displays an array of `string`s, reverses it, and displays it again.
//
// ### Arguments
//
// - None
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main() {
    vector<string> arr = {"Henry", "Johannes", "Charles", "Sylvester", "Emily"};

    cout << "Original array: ";
    displayArray(arr.data(), arr.size());
    cout << '\n';

    reverseArray(arr.data(), arr.size());

    cout << "Reversed array: ";
    displayArray(arr.data(), arr.size());
    cout << '\n';
}

void reverseArray(string* arr, size_t n_arr) {
    for (size_t a = 0, b = n_arr - 1; a < b; a++, b--) {
        std::swap(arr[a], arr[b]);
    }
}

void displayArray(string* arr, size_t n_arr) {
    if (n_arr == 0) {
        return;
    }

    cout << arr[0];

    for (size_t i = 1; i < n_arr; i++) {
        cout << ' ';
        cout << arr[i];
    }
}
