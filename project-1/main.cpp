// COMSC-210 | Lab 28 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

// Import necessary headers
#include <filesystem>
#include <list>
#include <fstream>
#include <map>
#include <array>
#include <print>

// Use namespace std
using namespace std;

// Declare `print_stats`
void print_stats(map<int, array<list<int>, 3>> state);

// `main` function
int main(int argc, const char** argv) {
    // Process executible path into input directory
    auto exe_file = filesystem::path(argv[0]);
    auto exe_dir = exe_file.parent_path();
    auto input_file = exe_dir / "input.txt";

    // Load input file into communal job queue (100 items)

    // Open file
    ifstream f(input_file);

    // Define temporary variables
    string buf;
    list<int> jobs;

    // For each line in the file
    while (getline(f, buf)) {
        // Convert and add it to the job queue
        jobs.push_back(stoi(buf));
    } // End loop

    // Close file
    f.close();

    ifstream input(input_file);

    // Define state map
    map<int, array<list<int>, 3>> compute_cluster;

    // Iterate across the compute nodes using the modulo operator and queue
    // jobs into Pending queues until the communal job queue is empty
    for (size_t i = 0; !jobs.empty(); i = (i + 1) % compute_cluster.size()) {
        compute_cluster[i][0].push_back(jobs.front());
        jobs.pop_front();
    }

    // Announce starting state
    println("Starting statistics:");

    // Display current compute cluster status

    // Announce time stepping
    println("Beginning time-stepping...");

    // Tick loop (26 times)
    for (size_t i = 0; i < 26; i++) {
        for (auto& node : compute_cluster) {
        // For each compute node, run `tick()` on its 3-list array

            // Display current compute cluster status
        
        // End for loop

    } // End tick loop

    // Announce time stepping finished
    println("Time-stepping finished.");

    // Display current compute cluster status
    println("Final cluster statistics:");

} // End `main` function

// 'print_stats' function
void print_stats(map<int, array<list<int>, 3>> state) {

    
} // End 'print_stats' function
