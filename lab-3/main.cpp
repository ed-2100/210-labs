// COMSC-210 | Lab 3 | Edwin Burwell

#include <cstdint>
#include <string>
#include <chrono>
#include <iostream>
#include <regex>

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

    string date_buf;
    cout << "Date Established (MMDDYYYY):" << flush;
    getline(cin, date_buf);

    const regex date_subregex("([0-9]{2})([0-9]{2})([0-9]{4})");
    smatch pieces_match;
    
    if (!regex_match(date_buf, pieces_match, date_subregex)) {
        cout << "Improper date entry!\n";
        return false;
    }

    

    return true;
}
