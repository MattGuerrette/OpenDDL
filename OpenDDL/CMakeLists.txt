
file(GLOB_RECURSE OpenDDL_SOURCES
    "Code/*.cpp"
    "Code/*.h"
)
add_library(OpenDDL STATIC
    ${OpenDDL_SOURCES}
)
target_include_directories(OpenDDL PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Code>
    $<INSTALL_INTERFACE:include/OpenDDL>
)
