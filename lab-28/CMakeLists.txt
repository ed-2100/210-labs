add_executable(lab-28 main.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/colors.txt
    colors.txt
    @ONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/names.txt
    names.txt
    @ONLY
)
