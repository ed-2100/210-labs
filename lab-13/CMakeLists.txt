add_executable(lab-13 main.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/210-lab-13-grades.txt
    210-lab-13-grades.txt
    @ONLY
)
