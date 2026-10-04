#include <filesystem>

#include "list.h"

using namespace std;

class Movie {

};

int main(int argc, const char** argv) {
    filesystem::path exe_path(argv[0]);

    auto exe_dir = exe_path.parent_path();
    auto input_path = exe_dir / "input.txt";
    


}
