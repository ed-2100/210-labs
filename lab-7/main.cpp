#include <string>
#include <vector>

using namespace std;

int main() {
    
}

void reverseArray(string* arr, size_t n_arr) {
    for (size_t a = 0, b = n_arr - 1; a < b; a++, b--) {
        string temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }
}

void displayArray(string* arr, size_t n_arr) {

}
