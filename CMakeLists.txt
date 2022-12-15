cmake_minimum_required(VERSION 3.20)
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
    set(multi LIBRARIES SOURCES)
    cmake_parse_arguments(ADD_LIB "" "" "${multi}" ${ARGN})
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

add_puzzle(4a LIBRARIES parser)
add_puzzle(4b LIBRARIES parser)

add_puzzle(5a LIBRARIES parser)
add_puzzle(5b LIBRARIES parser)

add_puzzle(6a)
add_puzzle(6b)

add_lib(dentry dentry.cpp LIBRARIES parser)
add_puzzle(7a LIBRARIES parser dentry)
add_puzzle(7b LIBRARIES parser dentry)

add_lib(trees trees.cpp LIBRARIES parser)
add_puzzle(8a LIBRARIES parser trees)
add_puzzle(8b LIBRARIES parser trees)

add_puzzle(9a LIBRARIES parser)
add_puzzle(9b LIBRARIES parser)

add_puzzle(10a LIBRARIES parser)
add_puzzle(10b LIBRARIES parser)

add_puzzle(11a LIBRARIES parser)
add_puzzle(11b LIBRARIES parser)
