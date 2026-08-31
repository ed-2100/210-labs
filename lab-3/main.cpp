// COMSC-210 | Lab 3 | Edwin Burwell
//
// Note:
//   The coding conventions require that input is fully validated.
//   Aside from input validation, this code is as minimal as possible.

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
    float n_croissant;
};

bool input_restraunt(Restraunt &rr);
bool input_est(Time &t);
bool input_phone(string& phone);
bool input_croissants(float& n_croissant);

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

    const regex date_regex("([0-9]{2})([0-9]{2})([0-9]{4})");
    smatch matches;
    
    if (!regex_match(date_buf, matches, date_regex)) {
        cerr << "Improper date entry!\n";
        return false;
    }

    tm time_buf;

    // Note:
    //   stoi usually throws exceptions on parsing errors,
    //   but this code is safe, because our input is
    //   already validated by the regex.
    time_buf.tm_mon  = stoi(matches[1]);
    time_buf.tm_mday = stoi(matches[2]);
    time_buf.tm_year = stoi(matches[3]);

    t = chrono::system_clock::from_time_t(mktime(&time_buf));
}

bool input_phone(string& phone) {
    string phone_buf;
    cout << "Phone Number ((xxx) xxx-xxx):" << flush;
    getline(cin, phone_buf);

    const regex phone_regex("\\([0-9]{3}\\) [0-9]{3}-[0-9]{3}");
    smatch matches;

    if (!regex_match(phone_buf, matches, phone_regex)) {
        cerr << "Improper phone number entry!\n";
        return false;
    }

    phone = std::move(phone_buf);
}

bool input_croissants(float& n_croissant) {
    string croissant_buf;
    cout << "Phone Number ((xxx) xxx-xxx):" << flush;
    getline(cin, phone_buf);

}
