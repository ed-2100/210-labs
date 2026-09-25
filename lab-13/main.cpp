#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <span>

using namespace std;

struct Student {
    uint32_t id;
    float grade;
};

void read_grades(vector<Student> &students, filesystem::path file);

void sort(span<Student> students);

void write_grades(const vector<Student> &students, filesystem::path file);

size_t min_score(span<Student> students);

int main(int argc, const char** argv) {
    filesystem::path exe_path(argv[0]);

    auto exe_dir = exe_path.parent_path();

    auto grades_path = exe_dir / "210-lab-13-grades.txt";
    auto sorted_grades_path = exe_dir / "210-lab-13-grades-sorted.txt";

    vector<Student> students;

    read_grades(students, grades_path);

    cout << "Read " << students.size() << " student records\n" << flush;

    sort(students);

    cout << "Sorted results written to " << sorted_grades_path.filename() << "\n\n" << flush;

    write_grades(students, sorted_grades_path);

    cout << "--- Summary Statistics ---\n" << flush; 
    
    auto min = min_score(students);

    cout << "Minimum Score: " << students[min].grade << " (Student ID: " << students[min].id << ")\n";
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

void sort(span<Student> students) {
    if (students.size() < 2) return;
    
    for (size_t i = 0; i < students.size() - 1; i++) {
        size_t min = i;

        for (size_t j = i + 1; j < students.size(); j++) {
            if (students[j].id < students[min].id) {
                min = j;
            }
        }

        if (i != min) {
            swap(students[i], students[min]);
        }
    }
}

void write_grades(const vector<Student> &students, filesystem::path file) {
    ofstream grades_file(file, _S_out | _S_trunc);

    for (const Student& student : students) {
        grades_file << student.id << ' ' << student.grade << '\n';
    }
}

size_t min_score(span<Student> students) {
    size_t min = 0;

    for (size_t i = 1; i < students.size(); i++) {
        if (students[i].grade < students[min].grade) {
            min = i;
        }
    }

    return min;
}

size_t max_score(span<Student> students) {
    size_t max = 0;

    for (size_t i = 1; i < students.size(); i++) {
        if (students[i].grade > students[max].grade) {
            max = i;
        }
    }

    return max;
}
