add_executable(lab-26 main.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/codes.txt
    codes.txt
    @ONLY
)
