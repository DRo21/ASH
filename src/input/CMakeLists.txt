add_library(input
    tokenizer.c
)

target_include_directories(input PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/input
)