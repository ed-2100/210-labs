// COMSC-210 | Lab 17 | Edwin Burwell
//
// Note: This may contain features from newer C++ versions, such as C++23.

#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <cfloat>
#include <ranges>
#include <format>

#include "list.h"

using namespace std;
using namespace mylist;

// The `Review` struct.
//
// Holds information pertaining to a
// user's review on a movie.
struct Review {
    float rating;
    string comment;
};

// The `Movie` class.
//
// Stores movie metadata, including
// reviews.
class Movie {
private:
    string m_title;
    List<Review> m_reviews;
public:
    // Sets the title of the movie.
    //
    // ### Arguments
    //
    //  - `title`: The new title for the movie.
    void set_title(string title);

    // Adds a review to the movie data.
    //
    // ### Arguments
    //
    // - `review`: The review to add to the movie.
    void add_review(Review review);

    // Displays the stored movie data to `stdout`.
    void display() const;
};

const char* titles[] = {
    "Lord of the Rings",
    "The Godfather",
    "Star Wars",
    "Jurassic Park"
};

// The main function.
//
// Loads movie metadata entries from a file and prints them to `stdout`.
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
    filesystem::path exe_path(argv[0]);

    auto exe_dir = exe_path.parent_path();
    auto input_path = exe_dir / "input.txt";
    
    List<Movie> movies;

    ifstream reviews_file(input_path);

    if (reviews_file.bad()) {
        cout << "Failed to open file " << input_path << '\n';
        return EXIT_FAILURE;
    }

    mt19937 gen(42);

    uniform_real_distribution<float> dist_value(1.0, nextafter(5.0, FLT_MAX));

    for (const char* title : titles) {
        Movie movie;

        movie.set_title(title);

        for (size_t i = 0; i < 3; i++) {
            Review review;

            review.rating = round(dist_value(gen) * 10) / 10;

            getline(reviews_file, review.comment);

            movie.add_review(move(review));
        }

        movies.push_back(move(movie));
    }

    for (const Movie& movie : movies) {
        movie.display();
        cout << '\n';
    }

    return EXIT_SUCCESS;
}

void Movie::set_title(string title) {
    m_title = move(title);
}

void Movie::add_review(Review review) {
    m_reviews.push_back(move(review));
}

void Movie::display() const {
    cout << "Movie Title: " << m_title << '\n';
    
    float average = 0;

    for (const auto& [i, review] : views::enumerate(m_reviews)) {
        cout << format("  > Review #{}: {:.1f}: {}\n", i + 1, review.rating, review.comment);
        average += review.rating;
    }

    average /= m_reviews.size();

    cout << format("  > Average: {:.1f}\n", average);
}
