add_executable(lab-4 main.cpp)



file(GLOB templateFiles RELATIVE ${srcDir} "${srcDir}/*")
foreach(templateFile ${templateFiles})
    set(srcTemplatePath ${srcDir}/${templateFile})
    if(NOT IS_DIRECTORY ${srcTemplatePath})
        message(STATUS "Configuring file ${templateFile}")
        configure_file(
                ${srcTemplatePath}
                ${destDir}/${templateFile}
                @ONLY)
    endif(NOT IS_DIRECTORY ${srcTemplatePath})
endforeach(templateFile)
