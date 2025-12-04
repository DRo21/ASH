add_library(execution
    executor.c
    builtins.c
    builtins/cd.c
    builtins/echo.c
    builtins/exit.c
)

target_include_directories(execution PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/execution
    ${CMAKE_SOURCE_DIR}/include/input
)