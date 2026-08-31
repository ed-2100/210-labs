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
bool input_croissant(float& n_croissant);

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
        cerr << "Improper phone number entry!";
        return false;
    }

    if (!input_croissant(rr.n_croissant)) {
        cerr << "Improper date entry!";
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
        return false;
    }

    tm time_buf;

    // Note:
    //   stoi usually throws exceptions on parsing errors,
    //   but this code is safe, because our input is
    //   already validated by the regex.
    auto month = stoi(matches[1]);
    auto day   = stoi(matches[2]);
    auto year  = stoi(matches[3]);

    if (month < 1 || month > 12) {
        return false;
    }

    // FIXME: Days are currently not validated against the month and year.
    if (day < 1 || day > 31) {
        return false;
    }

    time_buf.tm_mon  = month - 1;
    time_buf.tm_mday = day;
    time_buf.tm_year = month - 1900;

    t = chrono::system_clock::from_time_t(mktime(&time_buf));

    return true;
}

bool input_phone(string& phone) {
    string phone_buf;
    cout << "Phone Number ((xxx) xxx-xxx):" << flush;
    getline(cin, phone_buf);

    const regex phone_regex("\\([0-9]{3}\\) [0-9]{3}-[0-9]{3}");
    smatch matches;

    if (!regex_match(phone_buf, matches, phone_regex)) {
        return false;
    }

    phone = std::move(phone_buf);

    return true;
}

bool input_croissant(float& n_croissant) {
    string croissant_buf;
    cout << "Number of Croissants (any positive decimal number):" << flush;
    getline(cin, croissant_buf);

    float temp_croissant;
    size_t n_parsed;

    try {
        temp_croissant = stof(croissant_buf, &n_parsed);
    }
    catch (invalid_argument e) {
        return false;
    }
    catch (out_of_range e) {
        return false;
    }
    
    if (n_parsed != croissant_buf.size()) {
        return false;
    }

    n_croissant = temp_croissant;

    return true;
}
