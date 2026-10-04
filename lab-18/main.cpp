#include <filesystem>
#include <string>
#include <fstream>

#include "list.h"

using namespace std;
using namespace mylist;

struct Review {
    float rating;
    string review;
};

class Movie {
    string title;
    List<Review> reviews;

    void add_review(Review review);
    void display();
};

const char* titles[] = {
    "Lord of the Rings",
    "The Godfather",
    "Star Wars",
    "Jurassic Park"
};

int main(int argc, const char** argv) {
    filesystem::path exe_path(argv[0]);

    auto exe_dir = exe_path.parent_path();
    auto input_path = exe_dir / "input.txt";
    
    List<Movie> movies;

    ifstream reviews_file;

    for (const char* title : titles) {
        Movie movie;

        
    }
}


void Movie::add_review(Review review) {

}

void Movie::display() {

}
