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
    string comment;
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
        cout << format("  > Review #{}: {:.1f}: {}\n", i, review.rating, review.comment);
        average += review.rating;
    }

    average /= m_reviews.size();

    cout << format("  > Average: {:.1}\n", average);
}
