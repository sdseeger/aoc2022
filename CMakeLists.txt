cmake_minimum_required(VERSION 3.24)
project(advent_2022)

function(add_puzzle name)
    set(multi LIBRARIES SOURCES)
    cmake_parse_arguments(ADD_PUZZLE "" "" "${multi}" ${ARGN})
    add_executable(${name}
        src/${name}.cpp
        ${ADD_PUZZLE_SOURCES}
    )
    if(ADD_PUZZLE_LIBRARIES)
        target_link_libraries(${name} PRIVATE ${ADD_PUZZLE_LIBRARIES})
    endif()
    target_compile_features(${name} PRIVATE cxx_std_23)
    set_target_properties(${name} PROPERTIES CXX_EXTENSIONS OFF)
endfunction()

function(add_lib name)
    cmake_parse_arguments(ADD_LIB "" "" "LIBRARIES SOURCES" ${ARGN})
    add_library(${name} src/${name}.cpp)
    if(ADD_LIB_LIBRARIES)
        target_link_libraries(${name} PRIVATE ${ADD_LIB_LIBRARIES})
    endif()
    target_compile_features(${name} PRIVATE cxx_std_23)
    set_target_properties(${name} PROPERTIES CXX_EXTENSIONS OFF)
endfunction()

include_directories(inc)

add_lib(parser parser.cpp)

add_puzzle(1a LIBRARIES parser)
add_puzzle(1b LIBRARIES parser)

add_puzzle(2a LIBRARIES parser)
add_puzzle(2b LIBRARIES parser)

add_puzzle(3a LIBRARIES parser)
add_puzzle(3b LIBRARIES parser)

