#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
#include <set>
#include <vector>
#include <memory>
#include <format>

using namespace std;

struct BenchmarkX {
    virtual ~BenchmarkX() = default;
    virtual void run() = 0;
    virtual const char* name() = 0;
};

template <typename Task>
struct Benchmark : public BenchmarkX {
    Task t;
    string name;

    Benchmark() {
        
    }

    void run() override {

    }

    const char* name() override {
        return name;
    }
};

int main(int argc, const char** argv) {

}
