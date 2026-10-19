add_executable(lab-25 main.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/codes.txt
    codes.txt
    @ONLY
)
