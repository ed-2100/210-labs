// COMSC-210 | Lab 14 | Edwin Burwell
//
// Notes:
//
// - This code may contain features from newer C++ versions, such as C++23.
// - I forgot to start the autocommit script the first time around on this
//   assignment, so this is a rewrite. I will attach the video of both
//   iterations in the assignment submission so that you may ascertain
//   the authenticity of this code.

#include <vector>
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <utility>
#include <fstream>

using namespace std;

// The `Movie` class.
//
// Holds an 8-bit RGB value.
class Movie {
private:
    string m_title;
    string m_year_released;
    string m_screenwriter;

public:
    // ===============================
    // ===== Getters and Setters =====
    // ===============================

    constexpr const string& get_title() const noexcept {
        return m_title;
    }

    constexpr const string& get_year_released() const noexcept {
        return m_year_released;
    }

    constexpr const string& get_screenwriter() const noexcept {
        return m_screenwriter;
    }

    template <typename T>
    constexpr void set_title(T&& title) noexcept {
        m_title = forward<T>(title);
    }

    template <typename T>
    constexpr void set_year_released(T&& year_released) noexcept {
        m_year_released = forward<T>(year_released);
    }

    template <typename T>
    constexpr void set_screenwriter(T&& screenwriter) noexcept {
        m_screenwriter = forward<T>(screenwriter);
    }

    // =========================
    // ===== Class Methods =====
    // =========================

    // Prints the object's RGB value to `stdout`.
    void print() const;
};

// Reads movie metadata entries from a `file` into `movies`.
//
// ### Arguments
//
// - `movies`: The movie .
// - `file`: The path of the file to read from.
//
// ### Returns
//
// A boolean, which is true on success.
bool read_movies(vector<Movie>& movies, const filesystem::path& file);

int main(int argc, const char** argv) {
    vector<Movie> movies;

    filesystem::path exe_file(argv[0]);
    filesystem::path exe_dir = exe_file.parent_path();
    filesystem::path input_file = exe_dir / "input.txt";

    if (!read_movies(movies, input_file)) {
        cerr << "Failed to read movies." << endl;
    }

    if (movies.size() == 0) {
        return EXIT_SUCCESS;
    }

    movies[0].print();

    for (size_t i = 1; i < movies.size(); i++) {
        cout << '\n';
        movies[i].print();
    }
}

bool read_movies(vector<Movie>& movies, const filesystem::path& file) {
    movies.clear();

    ifstream movies_file;
    
    movies_file.open(file);

    if (movies_file.fail()) {
        cerr << "Failed to read from " << file << endl;
        return false;
    }

    size_t state = 0;
    string line;
    Movie movie;

    while (getline(movies_file, line)) {
        switch (state) {
            case 0:
                movie.set_title(move(line));
                break;
            case 1:
                movie.set_year_released(move(line));
                break;
            case 2:
                movie.set_screenwriter(move(line));
                movies.push_back(move(movie));
        }

        state += 1;

        if (state > 2) {
            state = 0;
        }
    }

    return true;
}

void Movie::print() const {
    cout << format(
        "Movie: {}\n    Year released: {}\n    Screenwriter: {}\n",
        m_title,
        m_year_released,
        m_screenwriter
    );
}
