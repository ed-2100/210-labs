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


void read_grades(vector<Student> &students, filesystem::path file);

void write_grades(const vector<Student> &students, filesystem::path file);

float mean_score(span<Student> students);

float median_score(span<Student> students);

float score_stddev(span<Student> students);

int main(int argc, const char** argv) {
    filesystem::path exe_path(argv[0]);

    auto exe_dir = exe_path.parent_path();

    auto grades_path = exe_dir / "210-lab-13-grades.txt";
    auto sorted_grades_path = exe_dir / "210-lab-13-grades-sorted.txt";

    vector<Student> students;

    read_grades(students, grades_path);

    cout << "Read " << students.size() << " student records\n" << flush;

    sort(
        students.begin(),
        students.end(),
        [](const Student& a, const Student& b) {
            return a.id < b.id;
        }
    );

    cout << "Sorted results written to " << sorted_grades_path.filename().string() << "\n\n" << flush;

    write_grades(students, sorted_grades_path);

    cout << "--- Summary Statistics ---\n" << flush; 
    
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
         << ")\n";

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
         << ")\n";
    
    float mean = mean_score(students);

    cout << "Mean Score: "
         << mean
         << '\n';

    float median = median_score(students);

    cout << "Median Score: "
         << median
         << '\n';

    float stddev = score_stddev(students);

    cout << "Standard Deviation: "
         << stddev
         << '\n';
}

void read_grades(vector<Student> &students, filesystem::path file) {
    students.clear();

    ifstream grades_file(file);

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
}

void write_grades(const vector<Student> &students, filesystem::path file) {
    ofstream grades_file(file, _S_out | _S_trunc);

    for (const Student& student : students) {
        grades_file << student.id << ' ' << student.grade << '\n';
    }
}

float mean_score(span<Student> students) {
    float sum = 0;

    for (const Student& student : students) {
        sum += student.grade;
    }

    sum /= students.size();

    return sum;
}

float median_score(span<Student> students) {
    vector<float> grades;

    grades.reserve(students.size());

    for (const Student& student : students) {
        grades.push_back(student.grade);
    }

    sort(grades.begin(), grades.end());

    size_t middle = students.size() >> 1;

    if (students.size() & 0x1) {
        return grades[middle];
    } else {
        return (grades[middle] + grades[middle + 1]) / 2;
    }
}

float score_stddev(span<Student> students) {
    float mean = mean_score(students);

    float variance = 0;

    for (const Student& student : students) {
        float difference = student.grade - mean;

        variance += difference * difference;
    }

    variance /= students.size();

    return sqrt(variance);
}
