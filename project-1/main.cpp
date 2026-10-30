// Import necessary headers
#include <filesystem>
#include <list>
#include <fstream>

// Use namespace std
using namespace std;

// `read_jobs` function declaration
list<int> read_jobs(filesystem::path file);

// `main` function
int main(int argc, const char** argv) {
    // Process executible path into input directory
    auto exe_file = filesystem::path(argv[0]);
    auto exe_dir = exe_file.parent_path();
    auto input_file = exe_dir / "input.txt";

    // Load input file into communal job queue (100 items)
    list<int> jobs = read_jobs(input_file);

    ifstream input(input_file);

    // Define state map

    // Iterate across the compute nodes using the modulo operator and queue
    // jobs into Pending queues until the communal job queue is empty

    // Announce starting state

    // Display current compute cluster status

    // Announce time stepping

    // Tick loop (25 times)

        // For each compute node, run `tick()` on its 3-list array

            // Display current compute cluster status
        
        // End for loop

    // End tick loop

    // Announce time stepping finished

    // Display current compute cluster status

    // End `main` function
}

// Begin `read_jobs` function
list<int> read_jobs(filesystem::path file) {
    ifstream f(file);

    string buf;
    list<int> jobs;

    while (getline(f, buf)) {
        jobs.push_back(stoi(buf));
    }
}

// End `read_jobs` function
