#include <filesystem>
#include <fstream>

using namespace std;

struct Student {
    uint32_t id;
    float grade;
};

int main(int argc, const char** argv) {
    filesystem::path exe_path(argv[0]);

    auto exe_dir = exe_path.parent_path();

    auto grades_path = exe_dir / "210-lab-13-grades.txt";

    ifstream grades_file();
}
