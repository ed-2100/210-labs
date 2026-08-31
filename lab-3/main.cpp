// COMSC-210 | Lab 3 | Edwin Burwell

#include <cstdint>
#include <string>
#include <chrono>

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

Restraunt input_restraunt() {
    
}
