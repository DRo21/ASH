cmake_minimum_required(VERSION 3.20)
project(ASH C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

# Add subdirectories for modules
add_subdirectory(src/core)
add_subdirectory(src/input)
add_subdirectory(src/execution)
add_subdirectory(src/environment)
add_subdirectory(src/extensions)
add_subdirectory(src/utils)

# Main executable
add_executable(ash src/core/shell.c)

# Link libraries from modules
target_link_libraries(ash
    core
    input
    execution
    environment
    extensions
    utils
)

# Make sure the compiler can find all headers in include/ folder
target_include_directories(ash PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/input
    ${CMAKE_SOURCE_DIR}/include/execution
    ${CMAKE_SOURCE_DIR}/include/environment
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/extensions
)
