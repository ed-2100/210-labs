// COMSC-210 | Lab 29 and Lab 30 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

// Import necessary headers
#include <filesystem>
#include <list>
#include <fstream>
#include <map>
#include <array>
#include <print>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstddef>
#include <exception>

// Use namespace std
using namespace std;

using ClusterState = map<int, array<list<int>, 3>>;

// Displays stats on a provided `ClusterState` to a specified `ostream`
//
// ### Arguments
//
//  - `os`: The stream to display to
//  - `state`: The state to display stats on
void print_stats(ostream& os, const ClusterState& compute_cluster);

// Tests `print_stats` for expected output.
//
// ### Returns
//
// A boolean value, which is true if the test passed.
bool test_print_stats();

// The `main` function
//
// Implements a simulation of compute cluster job handling, printing
// information about the state as the simulation progresses.
//
// ### Arguments
//
// - `argc`: The length of `argv`.
// - `argv`: The arguments passed to the program.
//
// ### Returns
//
// A signed integer value, where `0` means success.
int main(int argc, const char** argv) {
    // Process executable path into input directory
    auto exe_file = filesystem::path(argv[0]);
    auto exe_dir = exe_file.parent_path();
    auto input_file = exe_dir / "input.txt";

    // Open input file
    ifstream f(input_file);

    // Make sure it actually opened
    if (!f) {
        // And fail if it didn't
        println("Failed to open {}", input_file.string());
        return EXIT_FAILURE;
    }

    // Define temporary variables
    string buf;
    list<int> jobs;

    // For each line in the file
    while (getline(f, buf)) {
        // Convert and add it to the job queue
        int job_id;

        try {
            stoi(buf)
            jobs.push_back();
        } catch (const invalid_argument& e) {
            println("Failed to parse: {}", buf);
            return EXIT_FAILURE;
        } catch (const out_of_range& e) {
            println("Number too big: {}", buf);
            return EXIT_FAILURE;
        }
    }

    if (f.bad()) {
        println("An error was encountered while reading from {}", input_file.string());
        return EXIT_FAILURE;
    }

    // Close file
    f.close();

    // Define state map
    ClusterState compute_cluster;

    // Iterate across the compute nodes using the modulo operator and queue
    // jobs into Pending queues until the communal job queue is empty
    for (size_t i = 0; !jobs.empty(); i = (i + 1) % 4) {
        compute_cluster[i][0].push_back(jobs.front());
        jobs.pop_front();
    }

    if (!test_print_stats()) {
        println("`print_stats` unit test failed.\n");
        return EXIT_FAILURE;
    }

    // Announce starting state
    println("Starting statistics:");

    // Display current compute cluster status
    print_stats(cout, compute_cluster);

    // Announce time stepping
    println("\nBeginning time-stepping...");

    // Tick loop (26 times)
    for (size_t i = 0; i < 26; i++) {
        // For each compute node
        for (auto& [id, node] : compute_cluster) {
            // If Active not empty, then
            if (!node[1].empty()) {
                // De-queue one item from Active and queue it into Completed
                node[2].push_back(node[1].front());
                node[1].pop_front();
            }

            // While Pending not empty and length of active less than 5,
            while (!node[0].empty() && node[1].size() < 5) {
                // De-queue one item from Pending and queue it into Active
                node[1].push_back(node[0].front());
                node[0].pop_front();
            }
        }

        // Display current compute cluster status
        println("\nStats after timestep {}:", i + 1);
        print_stats(cout, compute_cluster);
    }

    // Announce time stepping finished
    println("\nTime-stepping finished.");

    // Display current compute cluster status
    println("\nFinal cluster statistics:");
    print_stats(cout, compute_cluster);

    // Return success
    return EXIT_SUCCESS;
}

void print_stats(ostream& os, const ClusterState& compute_cluster) {
    // Display table header
    println(os, "Node ID | Pending | Active | Completed");

    // For each node
    for (auto& [id, node] : compute_cluster) {
        // Display a row containing its ID and how many
        // Pending/Active/Completed jobs there are
        println(os, "{:>7} | {:>7} | {:>6} | {:>9}", id, node[0].size(), node[1].size(), node[2].size());
    }
}

bool test_print_stats() {
    ClusterState test_state = ClusterState {
        {0,  {
            list { 0, 1, 2, 3, 4, 5 },
            {6, 7, 8, 9},
            {10, 11}
        }},
        {10, {
            list {12, 13, 14, 15},
            {16, 17, 18, 19, 20, 21},
            {22, 23}
        }},
        {20, {
            list {24, 25},
            {26, 27, 28, 29},
            {30, 31, 32, 33, 34, 35}
        }},
    };

    const char expected[] = "Node ID | Pending | Active | Completed\n"
                            "      0 |       6 |      4 |         2\n"
                            "     10 |       4 |      6 |         2\n"
                            "     20 |       2 |      4 |         6\n";

    try {
        stringstream sbuf;
        print_stats(sbuf, test_state);

        if (sbuf.str().compare(expected) != 0) {
            return false;
        }
    } catch (const exception& e) {
        return false;
    }

    return true; // :)
}
