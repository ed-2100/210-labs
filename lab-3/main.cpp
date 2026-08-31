// COMSC-210 | Lab 3 | Edwin Burwell

#include <cstdint>
#include <string>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

struct Restraunt {
    string name;
    chrono::time_point<chrono::steady_clock> est;
    string address;
    string phone;
    uint32_t n_croissant;
};

bool input_restraunt(Restraunt &rr);

int main() {
    Restraunt rr;

    if (!input_restraunt(rr)) {
        cout << "Failed to properly parse!\n";
    }

    cout << "Exiting...\n";
}

bool input_restraunt(Restraunt &rr) {
    cout << "Name: ";
    getline(cin, rr.name);

    tm time_buf;

    cout << "Date Established (MMDDYYYY):" << flush;
    cin >> get_time(&time_buf, "%m%d%Y");

    if (cin.fail()) {
        return false;
    }

    return true;
}
