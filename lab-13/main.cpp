// COMSC-210 | Lab 13 | Edwin Burwell
//
// Note: This code may contain features from newer C++ versions, such as C++23.

#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <span>
#include <cmath>

using namespace std;

// The `Student` struct.
//
// Holds information about a student.
struct Student {
    uint32_t id;
    float grade;
};

// Reads grades from a `file` into `students`.
//
// ### Arguments
//
// - `students`: The student data.
// - `file`: The path of the file to read from.
//
// ### Returns
//
// A boolean, which is true on success.
bool read_grades(vector<Student> &students, filesystem::path file);

// Writes grades from `students` into a `file`.
//
// ### Arguments
//
// - `students`: The student data.
// - `file`: The path of the file to write to.
//
// ### Returns
//
// A boolean, which is true on success.
bool write_grades(span<const Student> students, filesystem::path file);

// Calculates the mean grade of `students`.
//
// ### Arguments
//
// - `students`: The student data.
//
// ### Returns
//
// The mean grade.
float mean_score(span<const Student> students);

// Calculates the median grade of `students` and prints it to `stdout`.
//
// ### Arguments
//
// - `students`: The student data.
void print_median(span<const Student> students);

// Calculates the standard deviation of the grades in `students`.
//
// ### Arguments
//
// - `students`: The student data.
//
// ### Returns
//
// The standard deviation of the grades.
float score_stddev(span<const Student> students);

// Sorts `students` based on `compare` in ascending order,
// where compare is the less-than operation.
//
// ### Arguments
//
// - `students`: The student data.
// - `compare`: The comparison function.
template <typename Comparison>
void selection_sort(span<Student> students, Comparison compare);

// The main function.
//
// Loads grades from a file, sorts them, writes them to
// a new file, and displays statistics about them.
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

    auto grades_path = exe_dir / "210-lab-13-grades.txt";
    auto sorted_grades_path = exe_dir / "210-lab-13-grades-sorted.txt";

    vector<Student> students;

    if (!read_grades(students, grades_path)) {
        cerr << "Failed to read grades." << endl;
        return EXIT_FAILURE;
    }

    cout << "Read " << students.size() << " student records" << endl;

    selection_sort(
        students,
        [](const Student& a, const Student& b) {
            return a.id < b.id;
        }
    );

    cout << "Sorted results written to " << sorted_grades_path.filename().string() << '\n' << endl;

    if (!write_grades(students, sorted_grades_path)) {
        cerr << "Failed to write grades." << endl;
        return EXIT_FAILURE;
    }

    cout << "--- Summary Statistics ---" << endl; 
    
    Student& min = *min_element(
        students.begin(),
        students.end(),
        [](const Student& a, const Student& b) {
            return a.grade < b.grade;
        }
    );

    cout << "Minimum Score: "
         << min.grade
         << " (Student ID: "
         << min.id
         << ")" << endl;

    Student& max = *max_element(
        students.begin(),
        students.end(),
        [](const Student& a, const Student& b) {
            return a.grade < b.grade;
        }
    );

    cout << "Maximum Score: "
         << max.grade
         << " (Student ID: "
         << max.id
         << ")" << endl;

    cout << "Mean Score: "
         << mean_score(students)
         << endl;

    print_median(students);

    cout << "Standard Deviation: "
         << score_stddev(students)
         << endl;

    return EXIT_SUCCESS; // :)
}

bool read_grades(vector<Student> &students, filesystem::path file) {
    students.clear();

    ifstream grades_file;
    
    grades_file.open(file);

    if (grades_file.fail()) {
        cerr << "Failed to read from " << file << endl;
        return false;
    }

    string line;
    string segment;

    while (getline(grades_file, line)) {
        stringstream line_buf(line);

        getline(line_buf, segment, ' ');

        uint32_t id = stoul(segment);
        
        getline(line_buf, segment, ' ');

        float grade = stof(segment);

        students.push_back(Student {
            .id = id,
            .grade = grade,
        });
    }

    return true;
}

bool write_grades(span<const Student> students, filesystem::path file) {
    ofstream grades_file;

    grades_file.open(file, _S_out | _S_trunc);

    if (grades_file.fail()) {
        cerr << "Failed to write to " << file << endl;
        return false;
    }

    for (const Student& student : students) {
        grades_file << student.id << ' ' << student.grade << '\n';
    }

    return true;
}

float mean_score(span<const Student> students) {
    float mean = 0;

    for (const Student& student : students) {
        mean += student.grade;
    }

    mean /= students.size();

    return mean;
}

void print_median(span<const Student> students) {
    vector<Student> temp(students.begin(), students.end());

    sort(
        temp.begin(),
        temp.end(),
        [](const Student& a, const Student& b) {
            return a.grade < b.grade;
        }
    );

    size_t middle = students.size() >> 1;

    cout << "Median Score: ";

    if (students.size() & 0x1) {
        float median = temp[middle].grade;

        cout << median
             << " (Student ID: "
             << middle;
    } else {
        float median = (temp[middle].grade + temp[middle + 1].grade) / 2;

        cout << median
             << " (Lower Student ID: "
             << temp[middle].id
             << " / Higher Student ID: "
             << temp[middle + 1].id;
    }

    cout << ")" << endl;
}

float score_stddev(span<const Student> students) {
    float mean = mean_score(students);

    float variance = 0;

    for (const Student& student : students) {
        float difference = student.grade - mean;

        variance += difference * difference;
    }

    variance /= students.size();

    return sqrt(variance);
}

template <typename Comparison>
void selection_sort(span<Student> students, Comparison compare) {
    for (size_t i = 0; i < students.size() - 1; i++) {
        size_t x = i;

        for (size_t j = i + 1; j < students.size(); j++) {
            if (compare(students[j], students[x])) {
                x = j;
            }
        }

        if (x != i) {
            swap(students[x], students[i]);
        }
    }
}
