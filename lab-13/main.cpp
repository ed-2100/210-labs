#include <filesystem>
#include <fstream>
#include <vector>

using namespace std;

struct Student {
    uint32_t id;
    float grade;
};

int main(int argc, const char** argv) {
    filesystem::path exe_path(argv[0]);

    auto exe_dir = exe_path.parent_path();

    auto grades_path = exe_dir / "210-lab-13-grades.txt";

    ifstream grades_file(grades_path);

    vector<Student> students;

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
void sort(T* arr, size_t n, ) {

}
