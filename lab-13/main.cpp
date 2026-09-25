#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

struct Student {
    uint32_t id;
    float grade;

    bool operator>(Student &rhs) {
        return id > rhs.id || (id == rhs.id && grade > rhs.grade);
    }
};

void read_grades(vector<Student> &students, filesystem::path file);

template <typename T>
void sort(T* arr, size_t n_arr);

void write_grades(const vector<Student> &students, filesystem::path file);

int main(int argc, const char** argv) {
    filesystem::path exe_path(argv[0]);

    auto exe_dir = exe_path.parent_path();

    auto grades_path = exe_dir / "210-lab-13-grades.txt";
    auto sorted_grades_path = exe_dir / "210-lab-13-grades-sorted.txt";

    vector<Student> students;

    cout << "Stage 1\n" << flush;

    read_grades(students, grades_path);

    cout << "Stage 2\n" << flush;

    sort(students.data(), students.size());

    cout << "Stage 3\n" << flush;

    write_grades(students, sorted_grades_path);

    cout << "Done\n" << flush;
}

void read_grades(vector<Student> &students, filesystem::path file) {
    students.clear();

    ifstream grades_file(file);

    string buf;
    string segment;

    while (getline(grades_file, buf)) {
        stringstream line_buf;

        getline(line_buf, segment);

        uint32_t id = stoul(segment);
        
        getline(line_buf, segment);

        float grade = stof(segment);

        students.push_back(Student {
            .id = id,
            .grade = grade,
        });
    }
}

template <typename T>
void sort(T* arr, size_t n_arr) {
    for (size_t i = 0; i < n_arr - 1; i++) {
        T* max = &arr[i];

        for (size_t j = i + 1; j < n_arr; j++) {
            if (arr[j] > *max) {
                max = &arr[j];
            }
        }

        if (&arr[i] != max) {
            swap(arr[i], *max);
        }
    }
}

void write_grades(const vector<Student> &students, filesystem::path file) {
    ofstream grades_file(file, _S_out | _S_trunc);

    for (const Student& student : students) {
        grades_file << student.grade << ' ' << student.id << '\n';
    }
}
