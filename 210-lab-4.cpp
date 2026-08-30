#include <iostream>
using namespace std;

// The entry point of the program.
//
// Sequentially prints integer numbers in the interval [1, 100] in ascending order to `stdout`.
// 
// Note: A trailing space follows each number, including the final number.
//
// ### Arguments
//
// - None
//
// ### Returns
//
// A signed integer exit code, where `0` means success.
int main() {
    for (int i = 1; i <= 100; i++)
        cout << i << " ";

    return 0;
}