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

    // Open input file
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

    // Define state map
    map<int, array<list<int>, 3>> compute_cluster;

    // Iterate across the compute nodes using the modulo operator and queue
    // jobs into Pending queues until the communal job queue is empty
    for (size_t i = 0; !jobs.empty(); i = (i + 1) % 4) {
        compute_cluster[i][0].push_back(jobs.front());
        jobs.pop_front();
    }

    // Announce starting state
    println("Starting statistics:");

    // Display current compute cluster status
    print_stats(compute_cluster);

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
            } // End if

            // While Pending not empty and length of active less than 5,
            while (!node[0].empty()) {
                // De-queue one item from Pending and queue it into Active
                node[1].push_back(node[0].front());
                node[0].pop_front();
            } // End while
        
        } // End for loop

        // Display current compute cluster status
        println("\nStats for timestep {}:", i);
        print_stats(compute_cluster);

    } // End tick loop

    // Announce time stepping finished
    println("\nTime-stepping finished.");

    // Display current compute cluster status
    println("\nFinal cluster statistics:");
    print_stats(compute_cluster);

} // End `main` function

// 'print_stats' function
void print_stats(map<int, array<list<int>, 3>> compute_cluster) {
    // Display table header
    println("Node ID | Pending | Active | Completed");

    // For each node
    for (auto& [id, node] : compute_cluster) {
        // Display a row containing its ID and how many
        // Pending/Active/Completed jobs there are
    
        println("{:>7} | {:>7} | {:>6} | {:>9}", id, node[0].size(), node[1].size(), node[2].size());
    } // End loop

} // End 'print_stats' function
