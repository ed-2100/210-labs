include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(lab-17 main.cpp)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    input.txt
    @ONLY
)
