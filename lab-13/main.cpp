#include <filesystem>
#include <fstream>
#include <vector>

using namespace std;

struct Student {
    uint32_t id;
    float grade;
};

template <typename T>
void sort(T* arr, size_t n_arr);

int main(int argc, const char** argv) {
    filesystem::path exe_path(argv[0]);

    auto exe_dir = exe_path.parent_path();

    auto grades_path = exe_dir / "210-lab-13-grades.txt";
    auto sorted_grades_path = exe_dir / "210-lab-13-grades-sorted.txt";

    vector<Student> students;

    read_grades(students, grades_path);

    sort(students.data(), students.size());

    write_grades(students, sorted_grades_path);
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
        T* current = &arr[i]
        T* max = current;

        for (size_t j = i + 1; j < n_arr; j++) {
            T& tmp = arr[j];

            if (tmp > *max) {
                max = &tmp;
            }
        }

        if (current != max) {
            swap(*current, *max);
        }
    }
}

void write_grades(const vector<Student> &students, filesystem::path file) {
    ofstream grades_file;

    grades_file.
}
