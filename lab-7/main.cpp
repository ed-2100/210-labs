#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    
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
