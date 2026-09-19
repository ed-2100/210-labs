add_executable(lab-9 main.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/test_sample.txt
    test_sample.txt
    @ONLY
)
