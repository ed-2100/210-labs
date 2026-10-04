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

struct Review {
    float rating;
    string review;
};

class Movie {
private:
    string m_title;
    List<Review> m_reviews;
public:
    void set_title(string title);
    void add_review(Review review);
    void display() const;
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

    ifstream reviews_file(input_path);

    mt19937 gen(42);

    uniform_int_distribution<uint32_t> dist_value(0.0, nextafter(5.0, FLT_MAX));

    for (const char* title : titles) {
        Movie movie;

        movie.set_title(title);

        for (size_t i = 0; i < 3; i++) {
            Review review;

            review.rating = dist_value(gen);

            getline(reviews_file, review.review);

            movie.add_review(move(review));
        }

        movies.push_back(move(movie));
    }

    for (const Movie& movie : movies) {
        movie.display();
    }
}

void Movie::set_title(string title) {
    m_title = move(title);
}

void Movie::add_review(Review review) {
    m_reviews.push_back(move(review));
}

void Movie::display() const {
    cout << "Movie Title: " << m_title;
    
    for (const auto& [review, i] : views::enumerate(m_reviews)) {
        cout << format("Review #{}: {}: {}", i, review.rating, review.review);
    
    //   > Review #1: 2.0: The best fantasy film ever made.
    //   > Review #2: 2.3: Too long, but the battles are incredible.
    //   > Review #3: 3.3: An epic journey with stunning visuals.
    //   > Average: 2.5
}
