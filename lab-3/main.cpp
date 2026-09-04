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

struct Restraunt {
    string name;
    Time est;
    string address;
    string phone;
    float n_croissant;
};

bool input_restraunt(istream &is, Restraunt &rr);
bool input_est(istream &is, Time &t);
bool input_phone(istream &is, string& phone);
bool input_croissant(istream &is, float& n_croissant);
void print_restraunt(const Restraunt &rr);

int main() {
    Restraunt rr;

    cout << "Taking user input for the first test...\n";

    if (!input_restraunt(cin, rr)) {
        cerr << "Failed to properly parse restraunt info!\n";
    }

    print_restraunt(rr);

    cout << "Parsing file input...\n";

    try {
        for(const auto &entry : filesystem::directory_iterator("./tests")) {
            if (entry.is_regular_file()) {
                ifstream file(entry.path());

                if (!input_restraunt(file, rr)) {
                    cerr << "Failed to properly parse file.\n"
                         << "Continuing...\n";
                    continue;
                }

                print_restraunt(rr);
            }
        }
    } catch (exception e) { // TODO: Specify exception.
        cout << e.what();
    }

    cout << "Exiting...\n";
}

bool input_restraunt(istream &is, Restraunt &rr) {
    cout << "Name: " << flush;
    getline(is, rr.name);

    if (!input_est(is, rr.est)) {
        cerr << "\nImproper date entry!\n";
        return false;
    }

    cout << "\nAddress: " << flush;
    getline(is, rr.address);

    if (!input_phone(is, rr.phone)) {
        cerr << "\nImproper phone number entry!\n";
        return false;
    }

    if (!input_croissant(is, rr.n_croissant)) {
        cerr << "\nImproper croissant count!\n";
        return false;
    }

    return true;
}

bool input_est(istream &is, Time &t) {
    string date_buf;
    cout << "\nDate Established (MMDDYYYY):" << flush;
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

bool input_phone(istream &is, string& phone) {
    string phone_buf;
    cout << "\nPhone Number ((XXX) XXX-XXXX):" << flush;
    getline(is, phone_buf);

    const regex phone_regex("\\([0-9]{3}\\) [0-9]{3}-[0-9]{4}");
    smatch matches;

    if (!regex_match(phone_buf, matches, phone_regex)) {
        return false;
    }

    phone = std::move(phone_buf);

    return true;
}

bool input_croissant(istream &is, float& n_croissant) {
    string croissant_buf;
    cout << "\nNumber of Croissants (any positive decimal number):" << flush;
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

    cout << "\nName:                 " << rr.name
         << "\nDate Established:     " << put_time(localtime(&tt_est), "%B %d, %Y")
         << "\nAddress:              " << rr.address
         << "\nPhone Number:         " << rr.phone
         << "\nNumber of Croissants: " << rr.n_croissant
         << "\n";
}
