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
#include <iomanip>
#include <fstream>
#include <filesystem>

using namespace std;

using Time = chrono::time_point<chrono::system_clock>;

// The `Restraunt` struct.
//
// Holds information about a restraunt.
struct Restraunt {
    string name;
    Time est;
    string address;
    string phone;
    float n_croissant;
};

// Populates a `Restraunt` struct using data from an input stream.
//
// Format: See other functions.
//
// ### Arguments
//
// - `is`: The stream to recieve properly formatted input from
// - `rr`: Struct to be populated
// - `prompt`: If true, will print user guidance to `stdout`
//
// ### Returns
//
// A boolean value that is true on success.
bool input_restraunt(istream &is, Restraunt &rr, bool prompt);

// Parses data from an input stream and populates `t`.
//
// Format: `MMDDYYYY`
//
// ### Arguments
//
// - `is`: The stream to recieve properly formatted input from
// - `t`: The time point to be populated
// - `prompt`: If true, will print user guidance to `stdout`
//
// ### Returns
//
// A boolean value that is true on success.
bool input_est(istream &is, Time &t, bool prompt);


// Parses data from an input stream and populates `phone`.
//
// Format: `(XXX) XXX-XXXX`
//
// ### Arguments
//
// - `is`: The stream to recieve properly formatted input from
// - `phone`: The phone number to be populated
// - `prompt`: If true, will print user guidance to `stdout`
//
// ### Returns
//
// A boolean value that is true on success.
bool input_phone(istream &is, string& phone, bool prompt);


// Parses data from an input stream and populates `n_croissant`.
//
// Format: A positive decimal number (eg. 123.4).
//
// ### Arguments
//
// - `is`: The stream to recieve properly formatted input from
// - `n_croissant`: The croissant index
// - `prompt`: If true, will print user guidance to `stdout`
//
// ### Returns
//
// A boolean value that is true on success.
bool input_croissant(istream &is, float& n_croissant, bool prompt);


// Pretty-prints a `Restraunt` struct.
//
// ### Arguments
//
// - `rr`: The `Restraunt` in question
//
// ### Returns
//
// A boolean value that is true on success.
void print_restraunt(const Restraunt &rr);


// The main function.
//
// Takes user input and parses files per assignment guidelines.
//
// ### Arguments
//
// - None
//
// ### Returns
//
// A signed integer, where `0` means success.
int main(int argc, char** argv) {
    Restraunt rr;

    cout << "Stage 1: Taking input from stdin for the first test...\n";

    if (!input_restraunt(cin, rr, true)) {
        cerr << "Failed to properly parse restraunt info!\n";
    }

    cout << "\n\nRestraunt struct contents:\n";

    print_restraunt(rr);

    cout << "\nStage 2: Parsing test-input files...\n\n";

    filesystem::path exe_dir(argv[0]);

    for(const auto &entry : filesystem::directory_iterator(exe_dir / "/tests")) {
        if (entry.is_regular_file()) {
            ifstream file(entry.path());

            cout << "Receiving file data...";

            if (!input_restraunt(file, rr, false)) {
                cerr << "Failed to properly parse file.\n"
                        << "Continuing...\n";
                continue;
            }

            cout << "\nRestraunt struct contents:\n";

            print_restraunt(rr);

            cout << "\n";
        }
    }

    cout << "Exiting...\n";
}

bool input_restraunt(istream &is, Restraunt &rr, bool prompt) {
    if (prompt) {
        cout << "Name: " << flush;
    }
    getline(is, rr.name);

    if (!input_est(is, rr.est, prompt)) {
        cerr << "\nImproper date entry!\n";
        return false;
    }

    if (prompt) {
        cout << "\nAddress: " << flush;
    }
    getline(is, rr.address);

    if (!input_phone(is, rr.phone, prompt)) {
        cerr << "\nImproper phone number entry!\n";
        return false;
    }

    if (!input_croissant(is, rr.n_croissant, prompt)) {
        cerr << "\nImproper croissant count!\n";
        return false;
    }

    return true;
}

bool input_est(istream &is, Time &t, bool prompt) {
    string date_buf;

    if (prompt) {
        cout << "\nDate Established (MMDDYYYY):" << flush;
    }

    getline(is, date_buf);

    const regex date_regex("([0-9]{2})([0-9]{2})([0-9]{4})");
    smatch matches;
    
    if (!regex_match(date_buf, matches, date_regex)) {
        return false;
    }

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

    tm time_buf = {
        .tm_mday = day,
        .tm_mon = month - 1,
        .tm_year = year - 1900,
    };

    t = chrono::system_clock::from_time_t(mktime(&time_buf));

    return true;
}

bool input_phone(istream &is, string& phone, bool prompt) {
    string phone_buf;

    if (prompt) {
        cout << "\nPhone Number ((XXX) XXX-XXXX):" << flush;
    }

    getline(is, phone_buf);

    const regex phone_regex("\\([0-9]{3}\\) [0-9]{3}-[0-9]{4}");
    smatch matches;

    if (!regex_match(phone_buf, matches, phone_regex)) {
        return false;
    }

    phone = std::move(phone_buf);

    return true;
}

bool input_croissant(istream &is, float& n_croissant, bool prompt) {
    string croissant_buf;

    if (prompt) {
        cout << "\nNumber of Croissants (any positive decimal number):" << flush;
    }

    getline(is, croissant_buf);

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

void print_restraunt(const Restraunt &rr) {
    time_t tt_est = chrono::system_clock::to_time_t(rr.est);

    cout <<   "Name:                 " << rr.name
         << "\nDate Established:     " << put_time(localtime(&tt_est), "%B %d, %Y")
         << "\nAddress:              " << rr.address
         << "\nPhone Number:         " << rr.phone
         << "\nNumber of Croissants: " << rr.n_croissant
         << "\n";
}
