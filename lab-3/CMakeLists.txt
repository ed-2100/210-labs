add_executable(lab-3 main.cpp)

file(
    GLOB
    testFiles
    RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*"
)

foreach(testFile ${testFiles})
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${testFile}
        ${testFile}
        @ONLY
    )
endforeach(testFile)
