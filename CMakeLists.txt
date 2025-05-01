cmake_minimum_required(VERSION 3.15)
project(ASH CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(ash ${SRC_FILES})
