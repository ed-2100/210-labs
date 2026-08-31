// COMSC-210 | Lab 3 | Edwin Burwell

#include <cstdint>
#include <string>
#include <chrono>
#include <iostream>
#include <regex>

using namespace std;

struct Restraunt {
    string name;
    chrono::time_point<chrono::system_clock> est;
    string address;
    string phone;
    uint32_t n_croissant;
};

bool input_restraunt(Restraunt &rr);
bool input_est()

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

    tm time_buf;

    // Note:
    //   stoi usually throws exceptions on parsing errors,
    //   but this code is safe, because our input is
    //   already validated by the regex.
    time_buf.tm_mon  = stoi(pieces_match[1]);
    time_buf.tm_mday = stoi(pieces_match[2]);
    time_buf.tm_year = stoi(pieces_match[3]);

    chrono::system_clock::from_time_t(mktime(&time_buf));

    return true;
}
