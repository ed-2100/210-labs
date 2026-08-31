// COMSC-210 | Lab 3 | Edwin Burwell

#include <cstdint>
#include <string>
#include <chrono>
#include <iostream>

using namespace std;

struct Restraunt {
    string name;
    chrono::time_point<chrono::steady_clock> est;
    string address;
    string phone;
    uint32_t n_croissant;
};

Restraunt input_restraunt();

int main() {
    
}

void input_restraunt(Restraunt* rr) {
    cout << "Name: ";
    getline(cin, rr->name);
    

    string date_buf;

    cout << "Date Established (MMDDYY):";

    getline()
}
