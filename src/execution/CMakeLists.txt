add_library(execution
    executor.c
    builtins/cd.c
    builtins/echo.c
    builtins/export.c
)

target_include_directories(execution PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/execution
    ${CMAKE_SOURCE_DIR}/include/input
)