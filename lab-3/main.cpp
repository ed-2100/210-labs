// COMSC-210 | Lab 3 | Edwin Burwell
//
// Note:
//   The coding conventions require that input is fully
//   validated, and the assignment requires that I don't
//   use stuff that wasn't already taught. Aside from input
//   validation, this code is as minimal as possible and
//   does not use any advanced constructs.

#include <cstdint>
#include <string>
#include <chrono>
#include <iostream>
#include <regex>

using namespace std;

using Time = chrono::time_point<chrono::system_clock>;

struct Restraunt {
    string name;
    Time est;
    string address;
    string phone;
    uint32_t n_croissant;
};

bool input_restraunt(Restraunt &rr);
bool input_est(Time &t);
bool input_phone(string phone);

int main() {
    Restraunt rr;

    if (!input_restraunt(rr)) {
        cerr << "Failed to properly parse restraunt info!\n";
    }

    cout << "Exiting...\n";
}

bool input_restraunt(Restraunt &rr) {
    cout << "Name: " << flush;
    getline(cin, rr.name);

    Time est;

    if (!input_est(est)) {
        return false;
    }

    cout << "Address: " << flush;
    getline(cin, rr.name);

    if (!input_phone(rr.phone)) {
        return false;
    }

    return true;
}

bool input_est(Time &t) {
    string date_buf;
    cout << "Date Established (MMDDYYYY):" << flush;
    getline(cin, date_buf);

    const regex date_subregex("([0-9]{2})([0-9]{2})([0-9]{4})");
    smatch pieces_match;
    
    if (!regex_match(date_buf, pieces_match, date_subregex)) {
        cerr << "Improper date entry!\n";
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

    t = chrono::system_clock::from_time_t(mktime(&time_buf));
}
