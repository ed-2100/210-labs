add_executable(lab-15 main.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    input.txt
    @ONLY
)
