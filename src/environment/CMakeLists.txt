add_library(environment
    variables.c
)

target_include_directories(environment PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/environment
)