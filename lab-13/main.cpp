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

    bool operator<(const Student& rhs) {
        return id < rhs.id || (id == rhs.id && grade < rhs.grade);
    }

    bool operator>(const Student& rhs) {
        return id > rhs.id || (id == rhs.id && grade > rhs.grade);
    }
};

void read_grades(vector<Student> &students, filesystem::path file);

void sort(Student* arr, size_t n_arr);

void write_grades(const vector<Student> &students, filesystem::path file);

int main(int argc, const char** argv) {
    filesystem::path exe_path(argv[0]);

    auto exe_dir = exe_path.parent_path();

    auto grades_path = exe_dir / "210-lab-13-grades.txt";
    auto sorted_grades_path = exe_dir / "210-lab-13-grades-sorted.txt";

    vector<Student> students;

    read_grades(students, grades_path);

    cout << "Read " << students.size() << " student records\n" << flush;

    sort(students.data(), students.size());

    cout << "Sorted results written to " << sorted_grades_path.filename() << "\n\n" << flush;

    write_grades(students, sorted_grades_path);

    cout << "--- Summary Statistics ---\n" << flush; 
    
    cout << "" << *min_element(students.begin(), students.end()).base();
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

void sort(Student* arr, size_t n_arr) {
    if (n_arr < 2) return;
    
    for (size_t i = 0; i < n_arr - 1; i++) {
        Student& current = arr[i];

        // if (&current != min) {
        //     swap(current, *min);
        // }
    }
}

void write_grades(const vector<Student> &students, filesystem::path file) {
    ofstream grades_file(file, _S_out | _S_trunc);

    for (const Student& student : students) {
        grades_file << student.id << ' ' << student.grade << '\n';
    }
}

size_t min(span<Student> students) {
    size_t min = 0;

    for (size_t i = 1; i < students.size(); i++) {
        if (students[i].id < students[min].id
            || (students[i].id == students[min].id
            && students[i].grade < students[min].grade)) {
            min = i;
        }
    }

    return min;
}

size_t max(span<Student> students) {
    size_t max = 0;

    for (size_t i = 1; i < students.size(); i++) {
        if (students[i].id > students[max].id
            || (students[i].id == students[max].id
            && students[i].grade > students[max].grade)) {
            max = i;
        }
    }

    return max;
}
