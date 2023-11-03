cmake_minimum_required (VERSION 3.10)

project (AoC2023)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_BUILD_TYPE Debug)

message(" -=- Creating build folder for Day : ${DAY} -=- ")

set (headers
    ${CMAKE_CURRENT_LIST_DIR}/include/day${DAY}.h
    ${CMAKE_CURRENT_LIST_DIR}/include/parsing.h
)
set (source
    ${CMAKE_CURRENT_LIST_DIR}/src/day${DAY}.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/parsing.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

message(" -=- Headers generated: ${headers} -=- ")
message(" -=- Source generated: ${source} -=- ")

add_executable (AoC2023 ${source} ${headers})

target_include_directories(AoC2023
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
)
set_target_properties(AoC2023
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY       "${CMAKE_CURRENT_LIST_DIR}/"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_LIST_DIR}/"
)
target_compile_definitions(AoC2023
    PRIVATE
    DAY=${DAY}
)
