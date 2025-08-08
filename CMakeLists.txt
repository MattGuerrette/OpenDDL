cmake_minimum_required(VERSION 3.28)
project(OpenDDL)

option (BUILD_EXAMPLES "Build examples" OFF)
option (BUILD_DOCUMENTATION "Build documentation" OFF)

# OpenDDL
add_subdirectory(OpenDDL)

if (BUILD_EXAMPLES)
    # Examples
    add_subdirectory(Example)
endif()

if (BUILD_DOCUMENTATION)
    find_package(Doxygen REQUIRED)
    if (${DOXYGEN_FOUND})
        set(DOXYGEN_ENABLE_PREPROCESSING YES)
        set(DOXYGEN_GENERATE_TREEVIEW YES)
        set(DOXYGEN_DISABLE_INDEX NO)
        #set(DOXYGEN_FULL_SIDEBAR NO)
        #set(DOXYGEN_HTML_EXTRA_FILES ${doxygenawesome_SOURCE_DIR}/doxygen-awesome-darkmode-toggle.js)
        #    set(DOXYGEN_HTML_EXTRA_STYLESHEET
        #    ${doxygenawesome_SOURCE_DIR}/doxygen-awesome.css
        #    ${doxygenawesome_SOURCE_DIR}/doxygen-awesome-sidebar-only-darkmode-toggle.css
        #    ${doxygenawesome_SOURCE_DIR}/doxygen-awesome-sidebar-only.css
        #)
        set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
        set(DOXYGEN_PROJECT_NAME "OpenDDL")
        #set(DOXYGEN_HTML_COLORSTYLE LIGHT)
        doxygen_add_docs(OpenDDL_Documentation
            README.md
            ${CMAKE_CURRENT_SOURCE_DIR}/OpenDDL
            ALL
        )
    endif ()
endif ()
